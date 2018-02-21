/*
** m2_redirection.c for mysh in /home/alkoleek/PSU_2016_minishell2
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun Apr  9 14:37:24 2017 Maxime DROUIN
** Last update Sun Apr  9 14:37:24 2017 Maxime DROUIN
*/

#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "my.h"

int	append_tofile(char **args, int i)
{
  int	fd;

  if ((fd = open(args[i + 1],  O_CREAT | O_WRONLY |
		 O_APPEND | O_LARGEFILE,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
		 S_IROTH | S_IWOTH)) == -1)
    return (-1);
  dup2(fd, STDOUT_FILENO);
  close(fd);
  return (0);
}

int	trunc_tofile(char **args, int i)
{
  int	fd;

  if ((fd = open(args[i + 1], O_CREAT | O_WRONLY |
		 O_TRUNC | O_LARGEFILE,
		 S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
		 S_IROTH | S_IWOTH)) == -1)
    return (-1);
  dup2(fd, STDOUT_FILENO);
  close(fd);
  return (0);
}

int	get_fromfile(char **args, int i)
{
  int	fd;

  if ((fd = open(args[i + 1], O_RDONLY | O_LARGEFILE)) == -1)
    {
      my_puterr(args[i + 1]);
      my_puterr(": No such file or directory.\n");
      return (-1);
    }
  dup2(fd, 0);
  close(fd);
  return (0);
}

int	get_fromuser(char **args, int i)
{
  char	*buffer;
  int	pipefd[2];

  if (g_shell_env.tty == 1)
    {
      if (pipe(pipefd) == -1)
	return (-1);
      while (my_strcmp(buffer, args[i + 1]) != 0)
	{
	  if ((buffer = get_next_line(g_shell_env.fd_zero)) == NULL
	      || my_strcmp(buffer, args[i + 1]) == 0)
	    {
	      close(pipefd[1]);
	      dup2(pipefd[0], 0);
	      close(pipefd[0]);
	      return (0);
	    }
	  write(pipefd[1], buffer, sizeof(buffer));
	  write(pipefd[1], "\n", 1);
	  close(pipefd[1]);
	}
    }
  return (0);
}
