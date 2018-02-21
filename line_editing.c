/*
** line_editing.c for 42sh in /home/alkoleek/PSU_2016_42sh
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun May 21 11:01:10 2017 Maxime DROUIN
** Last update Sun May 21 11:01:10 2017 Maxime DROUIN
*/

#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include "my.h"

void	normal_backspace(char **s, int *pos, int count, int i)
{
  char	*new;

  new = NULL;
  i = my_strlen((*s)) - 1;
  if (i > 0)
    new = my_realloc(new, i);
  else
    new = my_strdup("");
  while (count < i)
    {
      new[count] = (*s)[count];
      count = count + 1;
    }
  new[count] = 0;
  free((*s));
  (*s) = my_strdup(new);
  free(new);
  my_putstr("\33[2K\r");
  my_putstr(PS1);
  my_putstr((*s));
  (*pos) = my_strlen((*s));
}

void	special_backspace(char **s, int *pos, int count)
{
  int	r;
  char  *new;

  new = NULL;
  r = 0;
  (*pos) = (*pos) - 1;
  if ((*pos) == 0)
    count = count + 1;
  else
    (*s)[(*pos)] = -1;
  while ((*s)[count] != 0)
    {
      if ((*s)[count] != -1)
	{
	  new = my_realloc(new, r + 1);
	  new[r] = (*s)[count];
	  r = r + 1;
	}
      count = count + 1;
    }
  new[r] = 0;
  free((*s));
  (*s) = my_strdup(new);
  free(new);
  reprint_new(s, pos);
}
