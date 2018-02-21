/*
** tools.c for tools in /home/alkoleek/PSU_2016_minishell1
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Fri Jan 20 02:13:52 2017 Maxime DROUIN
** Last update Fri Jan 20 02:47:29 2017 Maxime DROUIN
*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "my.h"

int	quit_builtin(int ret_code)
{
  g_child_list = my_irealloc(g_child_list, g_child_count + 1);
  if ((g_child_list[g_child_count] = fork()) == 0)
    exit(ret_code);
  g_child_count = g_child_count + 1;
  return (0);
}

void	my_puterr(char *buffer)
{
  if (buffer != NULL)
    write(2, buffer, my_strlen(buffer));
}

int     is_relative(char *str)
{
  int   count;

  count = 0;
  while (str[count] != 0)
    {
      if (str[count] == '/')
	return (0);
      count = count + 1;
    }
  return (1);
}

int     line_check(char *line)
{
  if (line == NULL)
    {
      if (g_shell_env.tty == 1)
	my_putstr("exit\n");
      free(line);
      free_alias(g_alias);
      exit(g_shell_env.last_ret);
    }
  else if (line[0] == 0)
    return (1);
  return (0);
}

char    *free_nquit(char **x, char *ret)
{
  free((*x));
  return (ret);
}
