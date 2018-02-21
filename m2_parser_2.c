/*
** m2_parser_2.c for mysh in /home/alkoleek/PSU_2016_minishell2
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun Apr  9 15:06:07 2017 Maxime DROUIN
** Last update Sun Apr  9 15:06:07 2017 Maxime DROUIN
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"

char	*sub_fill_tab(char **temp, int *count_w, int *count_c)
{
  char	*out;

  out = my_strdup((*temp));
  free((*temp));
  (*temp) = NULL;
  (*count_w) = (*count_w) + 1;
  (*count_c) = 0;
  return (out);
}

char	*fill_buffer(char *temp, int *count_c, char c)
{
  temp = my_realloc(temp, (*count_c) + 1);
  temp[(*count_c)] = c;
  (*count_c) = (*count_c) + 1;
  return (temp);
}

char	*q_mark(char *temp, char *str, int *count, int *count_c)
{
  char	c;

  c = str[(*count)];
  (*count) = (*count) + 1;
  while (str[(*count)] != 0)
    {
      if (str[(*count)] == c)
	{
	  if (temp == NULL)
	    temp = my_strdup("");
	  return (temp);
	}
      else
	temp = fill_buffer(temp, count_c, str[(*count)]);
      (*count) = (*count) + 1;
    }
  my_puterr("Missing delimiter\n");
  return (NULL);
}

char	**fill_tab(char **tab, char *str, char *separator)
{
  int	count;
  int	count_w;
  int	count_c;
  char	*temp;

  init_fill_tab(&count, &count_c, &count_w, &temp);
  while (str[count] != '\0')
    {
      if (comp_delimiter(str[count], separator))
	{
	  if (!comp_delimiter(str[count], "\"'"))
	    {
	      if ((temp = q_mark(temp, str, &count, &count_c)) == NULL)
		return (NULL);
	    }
	  else
	    temp = fill_buffer(temp, &count_c, str[count]);
	  if (!comp_delimiter(str[count + 1], separator) ||
	      str[count + 1] == 0)
	    tab[count_w] = sub_fill_tab(&temp, &count_w, &count_c);
	}
      count = count + 1;
    }
  return (tab);
}

char	**parse_args(char *str, char *separator)
{
  int	i;
  int	j;
  char	**args;

  j = 0;
  if (str == NULL)
    return (NULL);
  if ((i = count_args(str, separator)) == 0)
    return (NULL);
  if ((args = malloc(sizeof(char *) * (i + 1))) == NULL)
    return (NULL);
  args[i] = NULL;
  while (j < i)
    {
      args[j] = NULL;
      j = j + 1;
    }
  if ((args = fill_tab(args, str, separator)) == NULL)
    return (NULL);
  if (args[0] == NULL)
    return (NULL);
  return (args);
}
