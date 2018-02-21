/*
** my_putnbr.c for navy in /home/alkoleek/PSU_2016_navy
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Tue Feb  7 22:42:32 2017 Maxime DROUIN
** Last update Tue Feb  7 22:42:34 2017 Maxime DROUIN
*/

#include "libmy.h"

int     my_putnbr(int nbr)
{
  if (nbr == -2147483648)
    my_putstr("-2147483648");
  if (nbr < 0)
    {
      nbr = -nbr;
      my_putchar('-');
    }
  if (nbr > 9)
    my_putnbr(nbr / 10);
  my_putchar(nbr % 10 + 48);
  return (0);
}
