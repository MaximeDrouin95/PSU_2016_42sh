/*
** parse_cmd.c for parse_cmd in /home/alkoleek/PSU_2016_minishell1
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Fri Jan 20 02:10:29 2017 Maxime DROUIN
** Last update Fri Jan 20 02:21:12 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include "my.h"

char    *path_cmd(char *path, char *name)
{
  char  *p_cmd;
  int   count;
  int   i;

  count = 0;
  if ((p_cmd = malloc(sizeof(char) * my_strlen(path) +
		      my_strlen(name) + 2)) == NULL)
    return (NULL);
  while (path[count] != 0)
    {
      p_cmd[count] = path[count];
      count = count + 1;
    }
  p_cmd[count] = '/';
  count = count + 1;
  i = 0;
  while (name[i] != 0)
    {
      p_cmd[count] = name[i];
      count = count + 1;
      i = i + 1;
    }
  p_cmd[count] = 0;
  return (p_cmd);
}
