/*
** env_cmd.c for env_cmd in /home/alkoleek/PSU_2016_minishell1
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Fri Jan 20 13:46:17 2017 Maxime DROUIN
** Last update Sun Jan 22 21:47:51 2017 Maxime DROUIN
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

int     p_env()
{
  int   i;

  i = 0;
  while (environ[i] != 0)
    {
      my_putstr(environ[i]);
      my_putchar('\n');
      i = i + 1;
    }
  quit_builtin(EXIT_SUCCESS);
  return (0);
}

int	error_setenv(char *str)
{
  if ((str[0] > 64 && str[0] < 91)
      || (str[0] > 96 && str[0] < 123)
      || (str[0] == 95))
    return (0);
  my_puterr("setenv: Variable name must begin ");
  my_puterr("with a letter.\n");
  return (1);
}

int	error_setenv2()
{
  my_puterr("setenv: Variable name must contain ");
  my_puterr("alphanumeric characters.\n");
  return (quit_builtin(EXIT_FAILURE) + 1);
}

int     set_env(char *name, char *value)
{
  if (name != NULL)
    {
      if (error_setenv(name))
	return (quit_builtin(EXIT_FAILURE) + 1);
      else if (my_str_isalpha(name))
	{
	  if (value == NULL)
	    {
	      if (setenv(name, "", 1) == -1)
		return (quit_builtin(EXIT_FAILURE) + 1);
	    }
	  else
	    if (setenv(name, value, 1) == -1)
	      return (quit_builtin(EXIT_FAILURE) + 1);
	  return (quit_builtin(EXIT_SUCCESS));
	}
      else
	return (error_setenv2());
    }
  else
    return (p_env());
}

int	unset_env(char *name)
{
  if (name != NULL)
    {
      if (unsetenv(name) == -1)
	return (quit_builtin(EXIT_FAILURE) + 1);
      return (quit_builtin(EXIT_SUCCESS));
    }
  else
    {
      my_puterr("unsetenv: Too few arguments.\n");
      quit_builtin(EXIT_FAILURE);
    }
  return (1);
}
