/*
** m2_builtins_exec.c for mysh in /home/alkoleek/PSU_2016_minishell2
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun Apr  9 15:17:43 2017 Maxime DROUIN
** Last update Sun Apr  9 15:17:43 2017 Maxime DROUIN
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

static int (*g_builtins[10])(t_llist *, int []) = {bui_cd,
						  bui_exit,
						  bui_setenv,
						  bui_unsetenv,
						  bui_env,
						  bui_echo,
						  bui_alias,
						  bui_unalias,
						  bui_history,
						  0};

char	*g_builtins_name[10] = {"cd",
				"exit",
				"setenv",
				"unsetenv",
				"env",
				"echo",
				"alias",
				"unalias",
				"history",
				0};

int	builtin_selector(t_llist *list)
{
  int	i;

  i = 0;
  while (g_builtins_name[i] != 0)
    {
      if (my_strcmp(g_builtins_name[i], (*list)->cmd[0]) == 0)
	return (i);
      i = i + 1;
    }
  if (my_strncmp((*list)->cmd[0], "!", 1) == 0)
    return (8);
  else
    return (-1);
}

int	exec_builtin(t_llist *list, int pipefd[])
{
  int	i;

  if ((i = builtin_selector(list)) == -1)
    return (1);
  else
    {
      if ((redirect_tofile((*list)->cmd)) == -1)
	return (-1);
      if ((g_builtins[i](list, pipefd)) == 1)
	return (-1);
      else
	return (0);
    }
  return (0);
}
