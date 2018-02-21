/*
** alias_func.c for 42sh in /home/alkoleek/PSU_2016_42sh
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Wed Apr 26 15:55:12 2017 Maxime DROUIN
** Last update Wed Apr 26 15:55:12 2017 Maxime DROUIN
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"

char	**replace_cmd(t_alias_list alias_temp, t_llist temp)
{
  char	**new;
  int	i;
  int	j;

  if ((new = malloc(sizeof(char *) * (tab_len(alias_temp->replace)
				      + tab_len(temp->cmd)))) == NULL)
    return (NULL);
  i = 0;
  while (alias_temp->replace[i] != 0)
    {
      new[i] = my_strdup(alias_temp->replace[i]);
      i = i + 1;
    }
  j = 1;
  while (temp->cmd[j] != 0)
    {
      new[i] = my_strdup(temp->cmd[j]);
      j = j + 1;
      i = i + 1;
    }
  new[i] = NULL;
  return (new);
}

int		replace_alias_core(t_llist temp, t_alias_list alias_temp)
{
  char		**x;

  if ((x = replace_cmd(alias_temp, temp)) == NULL)
    return (-1);
  free_2d(temp->cmd);
  temp->cmd = x;
  return (0);
}

int		replace_alias(t_llist list, t_alias_list alias,
			      t_alias_list blacklist, int i)
{
  t_llist	temp;
  t_alias_list	alias_temp;

  temp = list;
  alias_temp = alias;
  if (i > 1000)
    return (alias_loop());
  if (alias == NULL)
    return (0);
  while (temp != NULL)
    {
      while (alias_temp != NULL)
	{
	  if (my_strcmp(temp->cmd[0], alias_temp->initial) == 0
	      && (blacklist == NULL || alias_temp != blacklist))
	    if (replace_alias_core(temp, alias_temp) == -1
		|| replace_alias(list, alias, alias_temp, i + 1) == -1)
	      return (-1);
	  alias_temp = alias_temp->nxt;
	}
      alias_temp = alias;
      temp = temp->nxt;
    }
  return (0);
}

t_alias_list	delete_alias(t_alias_list alias, int i)
{
  t_alias_list	temp;
  t_alias_list	mark;
  int	x;

  x = 0;
  temp = alias;
  if (i == 0)
    return (alias->nxt);
  while (x < i - 1 && temp != NULL)
    {
      x = x + 1;
      temp = temp->nxt;
    }
  if (temp != NULL)
    {
      mark = temp;
      temp = temp->nxt;
      free(temp->initial);
      free_2d(temp->replace);
      temp = temp->nxt;
      mark->nxt = temp;
    }
  return (alias);
}

void	show_alias(t_alias_list alias)
{
  int	i;
  t_alias_list	temp;

  i = 0;
  temp = alias;
  while (temp != NULL)
    {
      my_putstr(temp->initial);
      i = 0;
      my_putchar('\t');
      while (temp->replace[i] != NULL)
	{
	  my_putstr(temp->replace[i]);
	  i = i + 1;
	  if (temp->replace[i] != NULL)
	    my_putchar(' ');
	}
      my_putchar('\n');
      temp = temp->nxt;
    }
}
