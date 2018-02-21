/*
** m2_cmdfill.c for mysh in /home/alkoleek/PSU_2016_minishell2
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun Apr  9 14:49:51 2017 Maxime DROUIN
** Last update Sun Apr  9 14:49:51 2017 Maxime DROUIN
*/

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"

int		count_cmd(t_llist list)
{
  int		i;
  t_llist	temp;

  temp = list;
  i = 0;
  while (temp != NULL)
    {
      i = i + 1;
      temp = temp->nxt;
    }
  return (i);
}

int		correct_cmd(t_llist list)
{
  t_llist	temp;

  temp = list;
  while (temp->nxt != NULL)
    temp = temp->nxt;
  if ((temp->type != 3 &&
       temp->type != 4 &&
       temp->type != 5)
      && temp->nxt == NULL)
    {
      my_puterr("Invalid null command.\n");
      return (-1);
    }
  return (0);
}

char	*get_varname(char *str, int *count)
{
  int	i;
  char	*name;

  name = NULL;
  i = 0;
  (*count) = (*count) + 1;
  while (str[(*count)] != 0 && str[(*count)] != '$')
    {
      name = my_realloc(name, i + 1);
      name[i] = str[(*count)];
      i = i + 1;
      (*count) = (*count) + 1;
    }
  (*count) = (*count) - 1;
  return (name);
}

char	*replace_var(char *str, int *count, char *word)
{
  char	*s;
  char	*x;

  if ((s = get_varname(str, count)) != NULL)
    {
      if (my_strcmp(s, "?") == 0)
	x = my_strdup(my_itoa(g_shell_env.last_ret));
      else if ((x = my_strdup(getenv(s))) == NULL)
	{
	  my_puterr(s);
	  my_puterr(": Undefined variable.\n");
	  return (NULL);
	}
      word = my_realloc(word, my_strlen(word) + my_strlen(x));
      word = my_strcat(word, x);
      free(s);
      free(x);
    }
  return (word);
}

t_llist	word_replace(t_llist list)
{
  char	*word;
  int	count;
  int	i;

  i = 0;
  while (list->cmd[i] != NULL)
    {
      word = my_strdup("");
      count = 0;
      while (list->cmd[i][count] != 0)
	{
	  if (list->cmd[i][count] == '$')
	    if ((word = replace_var(list->cmd[i], &count, word)) == NULL)
	      return (NULL);
	  count = count + 1;
	}
      if (word[0] != 0)
	list->cmd[i] = my_strdup(word);
      free(word);
      i = i + 1;
    }
  return (list);
}
