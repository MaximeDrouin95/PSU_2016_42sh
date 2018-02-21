/*
** my_tabdup.c for mysh in /home/alkoleek/PSU_2016_minishell2
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun Apr  9 15:03:51 2017 Maxime DROUIN
** Last update Sun Apr  9 15:03:51 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include "libmy.h"

int	tab_size(char **tab)
{
  int	i;

  i = 0;
  if (tab == NULL)
    return (0);
  while (tab[i] != 0)
    i = i + 1;
  return (i);
}

char	**tab_dup(char **tab)
{
  char	**out;
  int	i;

  i = 0;
  if (tab == NULL)
    return (NULL);
  if ((out = malloc(sizeof(char *) * tab_size(tab) + 1)) == NULL)
    return (NULL);
  while (tab[i] != 0)
    {
      out[i] = my_strdup(tab[i]);
      i = i + 1;
    }
  out[i] = 0;
  return (out);
}
