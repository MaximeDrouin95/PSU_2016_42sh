/*
** main.c for main in /home/alkoleek/PSU_2016_minishell1_bootstrap
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Mon Jan  9 14:42:12 2017 Maxime DROUIN
** Last update Sun Jan 22 17:04:06 2017 Maxime DROUIN
*/

#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "my.h"

t_shell_env	g_shell_env = {.last_ret = 0,
			       .fd_zero = 0,
			       .fd_one = 0,
			       .status = 0,
			       .tty = 0};

int	*g_child_list = NULL;
int	g_child_count = 0;
t_dlist	*g_history = NULL;
int	g_history_c = 0;

void	signal_handler(int signo)
{
  if (signo == SIGINT && g_child_count == 0)
    {
      if (g_shell_env.tty == 1)
	{
	  my_putstr("\n");
	  my_putstr(PS1);
	}
    }
}

void	signal_error(int status)
{
  if (WTERMSIG(status) == 11)
    my_puterr("Segmentation fault");
  if (WTERMSIG(status) == 4)
    my_puterr("Illegal instruction");
  if (WTERMSIG(status) == 6)
    my_puterr("Aborted");
  if (WTERMSIG(status) == 16)
    my_puterr("Stack fault");
  if (WTERMSIG(status) == 8)
    my_puterr("Floating exception");
  if (WTERMSIG(status) == 7)
    my_puterr("Bus error");
  if (WTERMSIG(status) == 9)
    my_puterr("Process killed");
  if (WCOREDUMP(status))
    my_puterr(" (core dumped)");
  if (WTERMSIG(status) != 13)
    my_puterr("\n");
  g_shell_env.last_ret = status;
  if (g_shell_env.last_ret == 11 || g_shell_env.last_ret == 8
     || g_shell_env.last_ret == 13 || g_shell_env.last_ret == 16
      || g_shell_env.last_ret == 6 || g_shell_env.last_ret == 9
      || g_shell_env.last_ret == 4)
    g_shell_env.last_ret = g_shell_env.last_ret + 0200;
}

int	main()
{
  put_oldpwd();
  if (init_shell() == -1)
    return (84);
  signal(SIGINT, signal_handler);
  signal(SIGTSTP, SIG_IGN);
  g_shell_env.fd_one = dup(1);
  g_shell_env.fd_zero = dup(0);
  g_shell_env.pgid = getpid();
  g_alias = load_alias_file(".42sh_alias");
  g_history = load_history(".history");
  while (1)
    {
      if (exec() == -1)
	g_shell_env.last_ret = 1;
    }
  free_alias(g_alias);
  exit(g_shell_env.last_ret);
}
