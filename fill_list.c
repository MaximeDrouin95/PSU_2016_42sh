/*
** fill_list.c for 42sh in /home/alkoleek/PSU_2016_42sh
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Thu May 11 11:47:55 2017 Maxime DROUIN
** Last update Thu May 11 11:47:55 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include "my.h"

t_llist	put_in_list(t_llist list, char **temp, int *count_c, int mark)
{
  list = add_last(list, (*temp), mark);
  free((*temp));
  (*temp) = NULL;
  (*count_c) = 0;
  return (list);
}

void	init_fill_list(int *count, int *count_c, int *i)
{
  (*count) = 0;
  (*count_c) = 0;
  (*i) = 0;
}

t_llist	end_fill_list(t_llist list, char **temp)
{
  if ((*temp) != NULL)
    {
      list = add_last(list, (*temp), 5);
      free((*temp));
      return (list);
    }
  else
    {
      if (list == NULL)
	my_puterr("Invalid null command.\n");
      return (list);
    }
}

char	*q_mark_list(char *temp, char *str, int *count, int *count_c)
{
  char	c;

  c = str[(*count)];
  (*count) = (*count) + 1;
  while (str[(*count)] != 0)
    {
      if (str[(*count)] == c)
	{
	  temp = fill_buffer(temp, count_c, str[(*count)]);
	  (*count) = (*count) + 1;
	  return (temp);
	}
      temp = fill_buffer(temp, count_c, str[(*count)]);
      (*count) = (*count) + 1;
    }
  my_puterr("Missing delimiter\n");
  return (NULL);
}

t_llist	fill_list(t_llist list, char *str, char **separator, char *temp)
{
  int	count;
  int	count_c;
  int	i;
  int	mark;

  init_fill_list(&count, &count_c, &i);
  while (str[count] != '\0')
    if ((i = comp_delimiter_2(str + count, separator, &mark)) != 0)
      count = count + 1;
    else if ((temp = fill_buffer(temp, &count_c, str[count])) != NULL)
      {
      if ((!comp_delimiter(str[count], "\"'")))
	{
	  if ((temp = q_mark_list(temp, str, &count, &count_c)) == NULL)
	    return (NULL);
	}
      else if ((i = comp_delimiter_2(str + count + 1, separator, &mark)) > 0)
	{
	  list = put_in_list(list, &temp, &count_c, mark);
	  count = count + i + 1;
	}
      else
	count = count + 1;
      }
  return (end_fill_list(list, &temp));
}
