/*
** autocomp_tools.c for 42sh in /home/alkoleek/PSU_2016_42sh
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun May 21 10:52:43 2017 Maxime DROUIN
** Last update Sun May 21 10:52:43 2017 Maxime DROUIN
*/

#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include "my.h"

char		**cpy_alias(int *x, char *str)
{
  t_alias_list  alias;
  char		**answer;

  answer = NULL;
  alias = g_alias;
  while (alias != NULL)
    {
      if (my_strncmp(alias->initial, str, my_strlen(str)) == 0
	  && check_dup_autocomp(alias->initial + my_strlen(str), answer))
	{
	  answer = tab_realloc(answer, (*x) + 1);
	  answer[(*x)] = my_strdup(alias->initial + my_strlen(str));
	  (*x) = (*x) + 1;
	}
      alias = alias->nxt;
    }
  return (answer);
}

char	**base_cmd_compl(int *x, char *str)
{
  char	**answer;
  int	i;

  i = 0;
  answer = cpy_alias(x, str);
  while (g_builtins_name[i] != 0)
    {
      if (my_strncmp(g_builtins_name[i], str, my_strlen(str)) == 0
	  && check_dup_autocomp(g_builtins_name[i] + my_strlen(str), answer))
	{
	  answer = tab_realloc(answer, (*x) + 1);
	  answer[(*x)] = my_strdup(g_builtins_name[i] + my_strlen(str));
	  (*x) = (*x) + 1;
	}
      i = i + 1;
    }
  return (answer);
}

char	*extract_path(char *str)
{
  char	*out;
  int	i;
  int	x;

  x = 0;
  out = NULL;
  i = my_strlen(str);
  while (i > 0 && str[i] != '/')
    i = i - 1;
  if (i == 0 && str[i] != '/')
    return (my_strdup("."));
  else
    {
      i = i + 1;
      while (x < i)
	{
	  out = my_realloc(out, x + 1);
	  out[x] = str[x];
	  x = x + 1;
	}
    }
  return (out);
}

char	*get_current_word(char *str, int *pos)
{
  char	*temp;
  int	i;

  i = 0;
  temp = NULL;
  while (i < (*pos))
    {
      temp = my_realloc(temp, i + 1);
      temp[i] = str[i];
      i = i + 1;
    }
  if (temp == NULL || temp[i - 1] == ' ')
    {
      if (temp != NULL)
	free(temp);
      return (my_strdup(""));
    }
  return (temp);
}
