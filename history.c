/*
** history.c for 42sh in /home/alkoleek/PSU_2016_42sh/bonus
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Wed May 17 09:39:58 2017 Maxime DROUIN
** Last update Wed May 17 09:39:58 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "my.h"

t_dlist         *dlist_new()
{
  t_dlist       *new;

  new = malloc(sizeof *new);
  if (new != NULL)
    {
      new->length = 0;
      new->head = NULL;
      new->tail = NULL;
    }
  return (new);
}

void            dlist_delete(t_dlist **list)
{
  t_history     *temp;
  t_history     *del;

  if (*list != NULL)
    {
      temp = (*list)->head;
      while (temp != NULL)
	{
	  del = temp;
	  temp = temp->next;
	  free(del);
	}
      free(*list);
      *list = NULL;
    }
}

t_dlist         *add_history(t_dlist *list, char *cmd)
{
  t_history     *new;

  if (list == NULL)
    list = dlist_new();
  if ((new = malloc(sizeof *new)) == NULL)
    return (list);
  new->cmd = my_strdup(cmd);
  new->prev = NULL;
  new->id = list->length;
  if (list->tail == NULL)
    {
      new->next = NULL;
      list->head = new;
      list->tail = new;
    }
  else
    {
      list->head->prev = new;
      new->next = list->head;
      list->head = new;
    }
  list->length = list->length + 1;
  return (list);
}

t_dlist		*load_history(char *filepath)
{
  t_dlist       *list;
  char		*line;
  int		fd;

  list = NULL;
  if ((fd = open(filepath, O_RDONLY)) == -1)
    return (list);
  list = dlist_new();
  while ((line = get_next_line(fd)) != NULL)
    {
      list = add_history(list, line);
      free(line);
    }
  close(fd);
  return (list);
}

int             save_history(char *cmd)
{
  int           fd;

  if ((fd = open(".history", O_APPEND | O_CREAT | O_RDWR, 0666)) == -1)
    return (-1);
  write(fd, cmd, my_strlen(cmd));
  write(fd, "\n", 1);
  close(fd);
  return (0);
}
