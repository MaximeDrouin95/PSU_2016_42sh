/*
** m2_builtins.c for mysh in /home/alkoleek/PSU_2016_minishell2
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun Apr  9 15:16:03 2017 Maxime DROUIN
** Last update Sun Apr  9 15:16:03 2017 Maxime DROUIN
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

int	bui_cd(t_llist *list, int pipefd[])
{
  int	i;

  if ((*list)->type == 2)
    if (dup2(pipefd[1], 1) == -1)
      return (quit_builtin(EXIT_FAILURE));
  i = my_cd((*list)->cmd);
  close(pipefd[1]);
  if (dup2(g_shell_env.fd_one, 1) == -1)
    return (quit_builtin(EXIT_FAILURE));
  if (i != 0)
    return (1);
  return (0);
}

int	bui_exit(t_llist *list, int pipefd[])
{
  int	i;

  if ((*list)->type == 2)
    if (dup2(pipefd[1], 1) == -1)
      return (quit_builtin(EXIT_FAILURE));
  if ((*list)->nxt == NULL || (*list)->type == 1)
    {
      my_putstr("exit\n");
      if ((*list)->cmd[1] != NULL)
	{
	  i = my_getnbr((*list)->cmd[1]);
	  if (i >= 0 && i <= 256)
	    exit(i);
	}
      free_alias(g_alias);
      exit(g_shell_env.last_ret);
    }
  else
    (*list) = switch_to_last((*list));
  close(pipefd[1]);
  if (dup2(g_shell_env.fd_one, 1) == -1)
    return (quit_builtin(EXIT_FAILURE));
  return (0);
}

int	bui_setenv(t_llist *list, int pipefd[])
{
  int	i;

  if ((*list)->type == 2)
    if (dup2(pipefd[1], 1) == -1)
      return (quit_builtin(EXIT_FAILURE));
  i = set_env((*list)->cmd[1], (*list)->cmd[2]);
  close(pipefd[1]);
  if (dup2(g_shell_env.fd_one, 1) == -1)
    return (quit_builtin(EXIT_FAILURE));
  if (i != 0)
    return (1);
  return (0);
}

int	bui_unsetenv(t_llist *list, int pipefd[])
{
  int	i;

  if ((*list)->type == 2)
    if (dup2(pipefd[1], 1) == -1)
      return (quit_builtin(EXIT_FAILURE));
  i = unset_env((*list)->cmd[1]);
  close(pipefd[1]);
  if (dup2(g_shell_env.fd_one, 1) == -1)
    return (quit_builtin(EXIT_FAILURE));
  if (i != 0)
    return (1);
  return (0);
}

int	bui_env(t_llist *list, int pipefd[])
{
  if ((*list)->type == 2)
    if (dup2(pipefd[1], 1) == -1)
      return (quit_builtin(EXIT_FAILURE));
  p_env();
  close(pipefd[1]);
  if (dup2(g_shell_env.fd_one, 1) == -1)
    return (quit_builtin(EXIT_FAILURE));
  return (0);
}
