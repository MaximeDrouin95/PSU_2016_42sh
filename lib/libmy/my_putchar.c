/*
** my_putchar.c for navy in /home/alkoleek/PSU_2016_navy
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Tue Feb  7 22:41:36 2017 Maxime DROUIN
** Last update Tue Feb  7 22:43:48 2017 Maxime DROUIN
*/

#include <unistd.h>
#include "libmy.h"

void	my_putchar(char c)
{
  write (1, &c, 1);
}
