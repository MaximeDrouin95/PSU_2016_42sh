/*
** my_showtab.c for tetris in /home/alkoleek/TEST_AREA/load_tetris
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Tue Feb 28 20:59:59 2017 Maxime DROUIN
** Last update Tue Feb 28 20:59:59 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include "libmy.h"

void	my_showtab(char **tab)
{
  int	i;

  i = 0;
  if (tab != NULL)
    {
      while (tab[i] != NULL)
	{
	  my_putstr(tab[i]);
	  my_putchar('\n');
	  i = i + 1;
	}
    }
}
