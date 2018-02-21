/*
** tab_tools.c for 42sh in /home/alkoleek/PSU_2016_42sh
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Thu May 11 10:58:05 2017 Maxime DROUIN
** Last update Thu May 11 10:58:05 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include "libmy.h"

int	tab_len(char **tab)
{
  int	i;

  i = 0;
  while (tab[i] != NULL)
    i = i + 1;
  return (i);
}

char	**tab_realloc(char **tab, int size)
{
  char	**new;
  int	j;
  int	i;

  i = 0;
  if (tab != NULL && (j = tab_len(tab)) > size)
    return (NULL);
  if ((new = malloc(sizeof(char *) * (size + 1))) == NULL)
    return (NULL);
  new[size] = 0;
  if (tab == NULL)
    return (new);
  while (i < j)
    {
      new[i] = my_strdup(tab[i]);
      i = i + 1;
    }
  while (i < size)
    {
      new[i] = (char *)-1;
      i = i + 1;
    }
  free_2d(tab);
  return (new);
}

char	**put_on_bottom(char **tab, int marker, int init_len)
{
  int	i;

  i = 0;
  while (init_len + i > marker)
    {
      tab[tab_len(tab) + i - 1] = my_strdup(tab[init_len + i - 1]);
      free(tab[init_len + i - 1]);
      tab[init_len + i - 1] = (char*)-1;
      i = i - 1;
    }
  return (tab);
}

char	**tab_cat(char **tab, char **cpy, int pos)
{
  int	j;

  j = 0;
  while (cpy[j] != NULL)
    {
      tab[pos] = my_strdup(cpy[j]);
      j = j + 1;
      pos = pos + 1;
    }
  return (tab);
}
