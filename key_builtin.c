/*
** key_builtin.c for 42sh in /home/alkoleek/PSU_2016_42sh
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun May 21 10:56:59 2017 Maxime DROUIN
** Last update Sun May 21 10:56:59 2017 Maxime DROUIN
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

int	kbui_autocmp(char **s, int *pos)
{
  char	**tmp;
  char	*current_word;

  current_word = get_current_word((*s), pos);
  if ((tmp = parse_args(current_word, " \t\"'")) == NULL)
    {
      free(current_word);
      current_word = my_strdup("");
      autocmp_file(current_word, s, pos);
    }
  else if (tmp[1] == NULL)
    {
      if (!is_relative(tmp[0]))
	autocmp_file(tmp[0], s, pos);
      autocmp_cmd(tmp[0], s, pos);
    }
  else
    autocmp_file(tmp[tab_len(tmp) - 1], s, pos);
  free(current_word);
  free_2d(tmp);
  return (0);
}

int		kbui_history_u(char **s, int *pos)
{
  t_dlist	*history;
  t_history	*temp;
  int		i;

  i = 0;
  history = g_history;
  my_putstr("\33[2K\r");
  my_putstr(PS1);
  if (history != NULL)
    {
      temp = history->head;
      while (temp->next != NULL && i < g_history_c)
	{
	  temp = temp->next;
	  i = i + 1;
	}
      my_putstr(temp->cmd);
      free((*s));
      (*s) = my_strdup(temp->cmd);
      (*pos) = my_strlen((*s));
      if (temp->next != NULL)
	g_history_c = g_history_c + 1;
    }
  return (0);
}

int     kbui_move_l(char **s, int *pos)
{
  static char *temp = NULL;

  if ((*s) == NULL)
    return (0);
  if (my_strcmp(temp, (*s)) != 0)
    {
      if (temp != NULL)
	free(temp);
      temp = my_strdup((*s));
    }
  if ((*pos) > 0 && (*s) != NULL)
    {
      my_putstr(tigetstr("cub1"));
      (*pos) = (*pos) - 1;
    }
  return (0);
}

int     kbui_move_r(char **s, int *pos)
{
  static char *temp = NULL;

  if ((*s) == NULL)
    return (0);
  if (my_strcmp(temp, (*s)) != 0)
    {
      if (temp != NULL)
	free(temp);
      temp = my_strdup((*s));
    }
  if ((*pos) < my_strlen(temp) && (*s) != NULL)
    {
      my_putstr(tigetstr("cuf1"));
      (*pos) = (*pos) + 1;
    }
  return (0);
}

int	kbui_backspace(char **s, int *pos)
{
  int	i;
  int	count;

  i = 0;
  count = 0;
  if ((*s) != NULL && (*pos) == my_strlen((*s)))
    normal_backspace(s, pos, count, i);
  else if ((*pos) > 0 && (*s) != NULL)
    special_backspace(s, pos, count);
  return (0);
}
