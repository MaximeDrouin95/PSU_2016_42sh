/*
** m2_builtins_2.c for 42sh in /home/alkoleek/PSU_2016_42sh
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Fri Apr 21 14:41:16 2017 Maxime DROUIN
** Last update Fri Apr 21 14:41:16 2017 Maxime DROUIN
*/

#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "my.h"

int	bui_echo(t_llist *list, int pipefd[])
{
  int	i;

  i = 1;
  if ((*list)->type == 2)
    if (dup2(pipefd[1], 1) == -1)
      return (quit_builtin(EXIT_FAILURE));
  while ((*list)->cmd[i] != NULL)
    {
      my_putstr((*list)->cmd[i]);
      if ((*list)->cmd[i + 1] != NULL)
	my_putchar(' ');
      i = i + 1;
    }
  my_putchar('\n');
  quit_builtin(EXIT_SUCCESS);
  close(pipefd[1]);
  if (dup2(g_shell_env.fd_one, 1) == -1)
    return (quit_builtin(EXIT_FAILURE));
  return (0);
}

int	check_dup_alias(char *str, t_alias_list alias)
{
  t_alias_list	temp;
  int	i;

  i = 0;
  temp = alias;
  while (temp != NULL)
    {
      if (my_strcmp(temp->initial, str) == 0)
	return (i);
      i = i + 1;
      temp = temp->nxt;
    }
  return (-1);
}

t_alias_list	alias_modify(int i, t_alias_list alias, t_llist *list,
			     char *separator)
{
  t_alias_list  temp;
  int	x;

  x = 0;
  temp = alias;
  while (x < i)
    {
      temp = temp->nxt;
      x = x + 1;
    }
  free(temp->replace);
  if ((temp->replace = parse_args((*list)->cmd[2], separator)) == NULL)
    {
      if ((temp->replace = malloc(sizeof(char *) * 2)) == NULL)
	return (NULL);
      temp->replace[0] = my_strdup("");
      temp->replace[1] = 0;
    }
  return (alias);
}

int	bui_alias(t_llist *list, int pipefd[])
{
  int	i;
  static char   separator[4] = {'=', ' ', '\t', 0};

  if ((*list)->type == 2)
    if (dup2(pipefd[1], 1) == -1)
      return (quit_builtin(EXIT_FAILURE));
  if ((*list)->cmd[1] == NULL)
     show_alias(g_alias);
  if ((*list)->cmd[1] != NULL && (*list)->cmd[2] != NULL)
    {
      if (check_alias((*list)->cmd) != 0)
	{
	  my_puterr("alias: Too dangerous to alias that.\n");
	  return (quit_builtin(EXIT_FAILURE));
	}
      if ((i = check_dup_alias((*list)->cmd[1], g_alias)) == -1)
	g_alias = add_next_alias(g_alias, (*list)->cmd, separator);
      else
	g_alias = alias_modify(i, g_alias, list, separator);
    }
  quit_builtin(EXIT_SUCCESS);
  close(pipefd[1]);
  if (dup2(g_shell_env.fd_one, 1) == -1)
    return (quit_builtin(EXIT_FAILURE));
  return (0);
}

int     bui_unalias(t_llist *list, int pipefd[])
{
  int	i;

  if ((*list)->type == 2)
    if (dup2(pipefd[1], 1) == -1)
      return (quit_builtin(EXIT_FAILURE));
  if ((*list)->cmd[1] != NULL)
    {
      if ((i = check_dup_alias((*list)->cmd[1], g_alias)) != -1)
	g_alias = delete_alias(g_alias, i);
    }
  quit_builtin(EXIT_SUCCESS);
  close(pipefd[1]);
  if (dup2(g_shell_env.fd_one, 1) == -1)
    return (quit_builtin(EXIT_FAILURE));
  return (0);
}
