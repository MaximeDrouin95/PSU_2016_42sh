/*
** my_realloc.c for mysh in /home/alkoleek
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun Apr  9 15:01:18 2017 Maxime DROUIN
** Last update Sun Apr  9 15:01:18 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include "libmy.h"

void	free_2d(char **tab)
{
  int	i;

  i = 0;
  if (tab != NULL)
    {
      while (tab[i] != 0)
	{
	  free(tab[i]);
	  i = i + 1;
	}
      free(tab);
    }
}

char	*my_realloc(char *old, int len)
{
  int	i;
  char	*new;

  i = 0;
  if (old != NULL && (my_strlen(old) > len || len == 0))
    {
      free(old);
      return (NULL);
    }
  if ((new = malloc(sizeof(char) * len + 1)) == NULL)
    return (NULL);
  new[len] = '\0';
  if (old == NULL)
    return (new);
  while (old[i] != 0)
    {
      new[i] = old[i];
      i = i + 1;
    }
  new[i] = 0;
  free(old);
  return (new);
}

int	my_intlen(int *tab)
{
  int	i;

  i = 0;
  while (tab != NULL && tab[i] != -1)
    i = i + 1;
  return (i);
}

int	*my_irealloc(int *old, int len)
{
  int   i;
  int	*new;

  i = 0;
  if (old != NULL && (my_intlen(old) > len || len == 0))
    {
      free(old);
      return (NULL);
    }
  if ((new = malloc(sizeof(int) * (len + 1))) == NULL)
    return (NULL);
  new[len] = -1;
  if (old == NULL)
    return (new);
  while (old[i] != -1)
    {
      new[i] = old[i];
      i = i + 1;
    }
  free(old);
  return (new);
}
