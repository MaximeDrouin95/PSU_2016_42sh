/*
** my_putstr.c for navy in /home/alkoleek/PSU_2016_navy
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Tue Feb  7 22:42:57 2017 Maxime DROUIN
** Last update Tue Feb  7 22:43:15 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include "libmy.h"

void	my_putstr(char *str)
{
  int	count;

  count = 0;
  while (str != (char *)-1 && str != NULL && str[count] != '\0')
    {
      my_putchar(str[count]);
      count = count + 1;
    }
}
