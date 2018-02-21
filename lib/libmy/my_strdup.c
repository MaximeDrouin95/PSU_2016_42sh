/*
** my_strdup.c for my_strdup in /home/alkoleek/CPool_Day08/task01
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Wed Oct 12 16:29:39 2016 Maxime DROUIN
** Last update Sat Jan 21 14:56:42 2017 Maxime DROUIN
*/

#include "stdlib.h"
#include "libmy.h"

char	*my_strdup(const char *src)
{
  char	*dest;

  if (src == NULL)
    return (NULL);
  if ((dest = malloc(sizeof(char) * (my_strlen((char *)src) + 1))) == NULL)
    return (NULL);
  return (my_strcpy(dest, (char *)src));
}
