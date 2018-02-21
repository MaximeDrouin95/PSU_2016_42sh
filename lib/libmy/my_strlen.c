/*
** my_strlen.c for navy in /home/alkoleek/PSU_2016_navy
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sat Feb 18 11:28:40 2017 Maxime DROUIN
** Last update Sat Feb 18 11:28:40 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include "libmy.h"

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str != NULL && str[i] != '\0')
    i = i + 1;
  return (i);
}
