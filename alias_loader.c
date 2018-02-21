/*
** alias_loader.c for 42sh in /home/alkoleek/PSU_2016_42sh
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Wed Apr 26 15:48:04 2017 Maxime DROUIN
** Last update Sat May 20 11:47:16 2017 Maxime BLANCHARD
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"

int	check_alias(char **parsed)
{
  static char *forbidden[3] = {"alias", "unalias", 0};
  int	i;

  i = 0;
  while (forbidden[i] != 0)
    {
      if (my_strcmp(forbidden[i], parsed[1]) == 0)
	return (-1);
      i = i + 1;
    }
  return (0);
}

char	**init_empty_replace()
{
  char	**new;

  if ((new = malloc(sizeof(char *) * 2)) == NULL)
    return (NULL);
  new[0] = "";
  new[1] = 0;
  return (new);
}

t_alias_list	add_next_alias(t_alias_list alias,
			       char **parsed,
			       char *separator)
{
  t_alias_list	new;
  t_alias_list temp;

  temp = alias;
  if ((new = malloc(sizeof(t_alias))) == NULL)
    return (NULL);
  if (parsed[0] != NULL && parsed[1] != NULL && parsed[2] != NULL)
    {
      if (check_alias(parsed) != 0)
	return (alias);
      new->initial = my_strdup(parsed[1]);
      if ((new->replace = parse_args(parsed[2], separator)) == NULL)
	new->replace = init_empty_replace();
      new->nxt = NULL;
      if (alias == NULL)
	return (new);
      else
	while (temp->nxt != NULL && my_strcmp(temp->initial, new->initial) != 0)
	  temp = temp->nxt;
      if (my_strcmp(temp->initial, new->initial) == 0)
	temp->replace = new->replace;
      else
	temp->nxt = new;
    }
  return (alias);
}

t_alias_list	load_alias_file(char *path)
{
  int	fd;
  char	*s;
  char	**parsed;
  t_alias_list	alias;
  static char   separator[4] = {'=', ' ', '\t', 0};

  alias = NULL;
  if ((fd = open(path, O_RDONLY)) == -1)
    return (NULL);
  while ((s = get_next_line(fd)) != NULL)
    {
      if ((parsed = parse_args(s, separator)) != NULL)
	{
	  if (my_strcmp(parsed[0], "alias") == 0)
	    alias = add_next_alias(alias, parsed, separator + 1);
	}
      free(s);
      free_2d(parsed);
    }
  close(fd);
  return (alias);
}
