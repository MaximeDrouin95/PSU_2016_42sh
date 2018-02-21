/*
** m2_waiters.c for mysh in /home/alkoleek/PSU_2016_minishell2
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Tue Apr 18 14:19:42 2017 Maxime DROUIN
** Last update Tue Apr 18 14:19:42 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include "my.h"

int	ret_handler()
{
  if (WIFEXITED(g_shell_env.status))
    g_shell_env.last_ret = WEXITSTATUS(g_shell_env.status);
  else if (WIFSIGNALED(g_shell_env.status))
    signal_error(g_shell_env.status);
  else if (WIFSTOPPED(g_shell_env.status))
    return (1);
  return (0);
}

int	full_wait_child(char list_save)
{
  int	x;
  int	j;
  int	i;

  x = 0;
  g_shell_env.last_ret = 0;
  j = 0;
  while (g_child_list != NULL && g_child_list[x] != -1)
    {
      g_shell_env.status = 0;
      while ((i = waitpid(g_child_list[x], &g_shell_env.status,
		      WUNTRACED | WCONTINUED)) > 0)
	{
	  if (ret_handler() == -1)
	    break;
	  if (list_save == 2 && j != EXIT_SUCCESS &&
	      g_shell_env.last_ret == EXIT_SUCCESS)
	    g_shell_env.last_ret = j;
	  j = g_shell_env.last_ret;
	}
      x = x + 1;
    }
  return (0);
}

int     exec_ifsuccess(char last_cmd)
{
  full_wait_child(last_cmd);
  if (g_shell_env.last_ret == EXIT_SUCCESS)
    return (0);
  else
    return (-1);
}

int     exec_iffailed(char last_cmd)
{
  full_wait_child(last_cmd);
  if (g_shell_env.last_ret == EXIT_SUCCESS)
    return (-1);
  else
    return (0);
}

int	no_wait_child(char c)
{
  if (c == -1)
    return (-1);
  return (0);
}
