/*
** m2_parser_1.c for mysh in /home/alkoleek/PSU_2016_minishell2
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun Apr  9 15:08:06 2017 Maxime DROUIN
** Last update Sun Apr  9 15:08:06 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

char	*clear_filename(char *str)
{
  int	count;
  char	*new_str;
  int	i;

  i = 0;
  count = my_strlen(str);
  while (str[count] != '/' && count >= 1)
    count = count - 1;
  if (str[count] == '/')
    count = count + 1;
  if ((new_str = malloc(sizeof(char) * (my_strlen(str) - count + 1))) == NULL)
    return (NULL);
  while (str[count] != 0)
    {
      new_str[i] = str[count];
      i = i + 1;
      count = count + 1;
    }
  new_str[i] = '\0';
  free(str);
  return (new_str);
}

int	count_quotation_mark(int *args, char *str, char *separator, int *count)
{
  char	c;

  c = str[(*count)];
  (*count) = (*count) + 1;
  while (str[(*count)] != 0)
    {
      if (str[(*count)] == c)
	{
	  if (!comp_delimiter(str[(*count) + 1], separator)
	      || str[(*count) + 1] == '\0')
	  (*args) = (*args) + 1;
	  return (0);
	}
      (*count) = (*count) + 1;
    }
  if (str[(*count)] == 0)
    (*args) = (*args) + 1;
  return (0);
}

int     count_args(char *str, char *separator)
{
  int   count;
  int   args;

  args = 0;
  count = 0;
  while (str[count] != '\0')
    {
      if (comp_delimiter(str[count], separator))
	{
	  if (!comp_delimiter(str[count], "\"'"))
	    count_quotation_mark(&args, str, separator, &count);
	  else
	    {
	      if (!comp_delimiter(str[count + 1], separator)
		  || str[count + 1] == '\0')
		args = args + 1;
	    }
	}
      count = count + 1;
    }
  return (args);
}

void    init_fill_tab(int *count, int *count_c, int *count_w, char **temp)
{
  (*count) = 0;
  (*count_c) = 0;
  (*count_w) = 0;
  (*temp) = NULL;
}
