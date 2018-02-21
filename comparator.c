/*
** comparator.c for 42Sh in /home/alkoleek/PSU_2016_42sh
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Thu May 11 11:50:09 2017 Maxime DROUIN
** Last update Thu May 11 11:50:09 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include "my.h"

int	comp_delimiter(char c, char *delimiter)
{
  int	i;

  i = 0;
  while (delimiter[i] != 0)
    {
      if (delimiter[i] == c)
	return (0);
      i = i + 1;
    }
  return (1);
}

int	comp_delimiter_2(char *str, char **separator, int *i)
{
  if (i == NULL)
    i = malloc(sizeof(int));
  (*i) = 0;
  while (separator[(*i)] != 0)
    {
      if (my_strncmp(str, separator[(*i)], my_strlen(separator[(*i)])) == 0)
	return (my_strlen(separator[(*i)]));
      (*i) = (*i) + 1;
    }
  return (0);
}
