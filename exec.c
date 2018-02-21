/*
** exec.c for exec in /home/alkoleek/PSU_2016_minishell1
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Fri Jan 20 02:15:02 2017 Maxime DROUIN
** Last update Sun Jan 22 17:14:43 2017 Maxime DROUIN
*/

#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"

char *g_delimiter[6] = {"&&", "||", "|", "&", ";", 0};
t_alias_list	g_alias = NULL;

char	**get_path()
{
  char	*buffer;
  char	**path;
  int	i;

  if ((buffer = malloc(sizeof(char) *
		       (i = confstr(_CS_PATH, NULL, 0)))) == NULL)
    return (NULL);
  if (confstr(_CS_PATH, buffer, i) == 0)
    return (NULL);
  if ((path = parse_args(buffer, ":\0")) == NULL)
    return (NULL);
  free(buffer);
  return (path);
}

int     find_and_exec(char **args)
{
  char  **path;
  char  *p_cmd;
  int   i;

  i = 0;
  if ((path = parse_args(getenv("PATH"), ":\0")) == NULL)
    path = get_path();
  while (path != NULL && path[i] != 0)
    {
      p_cmd = path_cmd(path[i], args[0]);
      if (access(p_cmd, X_OK) == 0)
	if (execve(p_cmd, args, environ) == -1)
	  exit(EXIT_FAILURE);
      i = i + 1;
      free(p_cmd);
    }
  my_puterr(args[0]);
  my_puterr(": Command not found.\n");
  exit(EXIT_FAILURE);
}

int     child_exec(char *cmd, char **args)
{
  struct stat	dir;

  if ((redirect_tofile(args)) == -1)
    exit(EXIT_FAILURE);
  if (stat(cmd, &dir) != -1)
    if (S_ISDIR(dir.st_mode))
      {
	my_puterr(cmd);
        my_puterr(": Permission denied.\n");
	exit(EXIT_FAILURE);
      }
  errno = 0;
  if (execve(cmd, args, environ) == -1)
    {
      if (is_relative(cmd))
	find_and_exec(args);
      my_puterr(cmd);
      if (errno == ENOEXEC)
	my_puterr(": Exec format error. Binary file not executable.\n");
      else
	my_puterr(": Command not found.\n");
      exit(EXIT_FAILURE);
    }
  exit(EXIT_SUCCESS);
}

char	*choose_getmode()
{
  char	*line;

  if (g_shell_env.tty == 1)
    {
      if ((line = shell_gnl(0)) == NULL)
	{
	  free(line);
	  return (NULL);
	}
    }
  else
    {
      line = get_next_line(0);
      if (line_check(line) != 0)
	{
	  free(line);
	  return (NULL);
	}
    }
  return (line);
}

int		exec()
{
  char		*line;
  t_llist	list;

  if (g_shell_env.tty == 1)
    my_putstr(PS1);
  if ((line = choose_getmode()) == NULL)
    return (0);
  g_history_c = 0;
  g_history = add_history(g_history, line);
  save_history(line);
  if ((list = fill_list(NULL, line, g_delimiter, NULL)) == NULL)
    return (-1);
  if (correct_cmd(list) == -1)
    return (-1);
  if (replace_alias(list, g_alias, NULL, 0) == -1)
    return (-1);
  exec_cmd(list);
  if (dup2(g_shell_env.fd_one, 1) == -1 ||
      dup2(g_shell_env.fd_zero, 0) == -1)
    return (-1);
  free(line);
  return (0);
}
