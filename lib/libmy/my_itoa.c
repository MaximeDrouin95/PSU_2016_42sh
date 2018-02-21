/*
** my_itoa.c for mysh in /home/alkoleek/PSU_2016_minishell2
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Tue Apr 18 03:05:22 2017 Maxime DROUIN
** Last update Tue Apr 18 03:05:22 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include "libmy.h"

char	*sub_itoa(char buffer[], int i)
{
  char	*out;
  int	j;

  j = 0;
  out = NULL;
  while (i >= 0)
    {
      out = my_realloc(out, j + 1);
      out[j] = buffer[i];
      i = i - 1;
      j = j + 1;
    }
  return (out);
}

char	*my_itoa(int nb)
{
  char	buffer[20];
  char	*out;
  int	i;

  i = 0;
  if (nb == 0)
    return ("0");
  else
    {
      while (nb > 0)
	{
	  buffer[i] = (nb % 10) + 48;
	  nb = nb / 10;
	  i = i + 1;
	}
      i = i - 1;
      out = sub_itoa(buffer, i);
    }
  return (out);
}
