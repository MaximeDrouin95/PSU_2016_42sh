/*
** alias_func_2.c for 42sh in /home/alkoleek/PSU_2016_42sh
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Thu May 11 13:37:26 2017 Maxime DROUIN
** Last update Thu May 11 13:37:26 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include "my.h"

int     alias_loop()
{
  my_puterr("Alias loop.\n");
  return (-1);
}

t_alias_list    del_alias(t_alias_list alias)
{
  t_alias_list  temp;

  temp = alias->nxt;
  if (alias != NULL)
    {
      free(alias->initial);
      free_2d(alias->replace);
      free(alias);
      return (temp);
    }
  else
    return (NULL);
}

void    free_alias(t_alias_list alias)
{
  while (alias != NULL)
    alias = del_alias(alias);
}
