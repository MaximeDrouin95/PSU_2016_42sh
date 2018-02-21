/*
** m2_redirector.c for mysh in /home/alkoleek/PSU_2016_minishell2
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun Apr  9 14:47:04 2017 Maxime DROUIN
** Last update Sun Apr  9 14:47:04 2017 Maxime DROUIN
*/

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"

int	(*redirection_func[4])(char **, int) = {append_tofile,
						trunc_tofile,
						get_fromfile,
						get_fromuser};

int	get_redire_nb(char **args, int *i)
{
  while (args[(*i)] != NULL)
    {
      if ((my_strcmp(args[(*i)], ">>")) == 0 && args[(*i) + 1] != NULL)
	return (0);
      else if ((my_strcmp(args[(*i)], ">")) == 0 && args[(*i) + 1] != NULL)
	return (1);
      else if ((my_strcmp(args[(*i)], "<")) == 0 && args[(*i) + 1] != NULL)
	return (2);
      else if ((my_strcmp(args[(*i)], "<<")) == 0 && args[(*i) + 1] != NULL)
	return (3);
      (*i) = (*i) + 1;
    }
  return (-1);
}

int     get_redire_nb2(char **args, int *i)
{
  while (args[(*i)] != NULL)
    {
      if ((my_strncmp(args[(*i)], ">>", 2)) == 0 && args[(*i)][2] != 0)
	return (0);
      else if ((my_strncmp(args[(*i)], ">", 1)) == 0 && args[(*i)][1] != 0)
	return (1);
      else if ((my_strncmp(args[(*i)], "<", 1)) == 0 && args[(*i)][1] != 0)
	return (2);
      else if ((my_strncmp(args[(*i)], "<<", 2)) == 0 && args[(*i)][2] != 0)
	return (3);
      (*i) = (*i) + 1;
    }
  return (-1);
}

int	redirect_tofile2(char **args)
{
  int	i;
  int	j;
  int	ret;

  i = 0;
  if (args == NULL || args[0] == NULL)
    {
      my_puterr("Invalid null command.\n");
      return (-1);
    }
  if ((j = get_redire_nb2(args, &i)) == -1)
    return (0);
  args[i] = args[i] + 1;
  ret = redirection_func[j](args, i - 1);
  while (args[i + 1] != 0)
    {
      args[i] = args[i + 1];
      i = i + 1;
    }
  args[i] = 0;
  if (ret == -1)
    return (-1);
  return (1);
}

int	redirect_tofile(char **args)
{
  int	i;
  int	j;
  int	ret;

  i = 0;
  if (args == NULL || args[0] == NULL)
    {
      my_puterr("Invalid null command.\n");
      return (-1);
    }
  if ((j = get_redire_nb(args, &i)) == -1)
    return (0);
  ret = redirection_func[j](args, i);
  while (args[i + 2] != 0)
    {
      args[i] = args[i + 2];
      i = i + 1;
    }
  args[i] = 0;
  if (ret == -1)
    return (-1);
  if (redirect_tofile(args) == -1)
    return (-1);
  return (1);
}
