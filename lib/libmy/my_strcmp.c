/*
** my_strcmp.c for my_strcmp.c in /home/Rubiks/CPool_Day06
** 
** Made by Maxime BLANCHARD
** Login   <Rubiks@epitech.net>
** 
** Started on  Tue Oct 11 07:35:35 2016 Maxime BLANCHARD
** Last update Tue Oct 11 20:06:03 2016 Maxime BLANCHARD
*/

#include <stdlib.h>
#include "libmy.h"

int	my_strcmp(char *s1, char *s2)
{
  int	count;

  count = 0;
  if (s1 == NULL || s2 == NULL)
    return (-1);
  while (s1[count] != '\0' || s2[count] != '\0')
    {
      if (s1[count] != s2[count])
	{
	  if (s1[count] > s2[count])
	    {
	      return (1);
	    }
	  if (s2[count] > s1[count])
	    {
	      return (-1);
	    }
	}
      count = count + 1;
    }
  return (0);
}
