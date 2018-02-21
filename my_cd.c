/*
** my_cd.c for my_cd in /home/alkoleek/alternatif/PSU_2016_minishell1
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Sun Jan 22 23:21:25 2017 Maxime DROUIN
** Last update Sun Jan 22 23:25:50 2017 Maxime DROUIN
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include "my.h"

void    put_oldpwd()
{
  char  pwd[256];

  setenv("OLDPWD", getcwd(pwd, 255), 1);
}

int    change_dir(char *filepath)
{
  put_oldpwd();
  if (access(filepath, R_OK) == 0)
    {
      chdir(filepath);
      quit_builtin(EXIT_SUCCESS);
      return (0);
    }
  else
    {
      my_puterr(filepath);
      my_puterr(": Permission denied\n");
      quit_builtin(EXIT_FAILURE);
    }
  return (1);
}

int             is_dir(char *filepath)
{
  struct stat   dir;

  if (stat(filepath, &dir) != -1)
    {
      if (S_ISDIR(dir.st_mode))
	return (1);
      else
	{
	  my_puterr(filepath);
	  my_puterr(": Not a directory.\n");
	  quit_builtin(EXIT_FAILURE);
	  return (0);
	}
    }
  else
    {
      my_puterr(filepath);
      my_puterr(": No such file or directory.\n");
      quit_builtin(EXIT_FAILURE);
      return (0);
    }
}

int     my_cd(char **args)
{
  if (args[1] == NULL)
    return (change_dir(getenv("HOME")));
  else
    {
      if (args[2] == NULL)
	{
	  if (args[1][0] == '-' && args[1][1] == 0)
	    return (change_dir(getenv("OLDPWD")));
	  else if (args[1][0] == '~' && args[1][1] == 0)
	    return (change_dir(getenv("HOME")));
	  else
	    {
	      if (is_dir(args[1]))
		return (change_dir(args[1]));
	    }
	}
      else
	{
	  my_puterr("cd: Too many arguments.\n");
	  quit_builtin(EXIT_FAILURE);
	}
    }
  return (1);
}
