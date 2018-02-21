/*
** readline.c for 42sh in /home/alkoleek/PSU_2016_42sh
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun May 21 10:44:24 2017 Maxime DROUIN
** Last update Sun May 21 10:44:24 2017 Maxime DROUIN
*/

#include <unistd.h>
#include <ncurses.h>
#include <curses.h>
#include <term.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "my.h"

static int (*g_keybuiltins[9])(char **, int *) = {kbui_move_l,
						  kbui_move_r,
						  kbui_history_u,
						  kbui_history_d,
						  kbui_backspace,
						  kbui_eol,
						  kbui_cariage,
						  kbui_autocmp,
						  0};

char	*save_buffer(int u, char **s)
{
  char	*out;
  int	i;

  out = NULL;
  i = 0;
  while ((*s)[u] != 0)
    {
      out = my_realloc(out, (i + 1));
      out[i] = (*s)[u];
      i = i + 1;
      u = u + 1;
    }
  out[i] = 0;
  return (out);
}

void	reprint_new(char **s, int *pos)
{
  int	u;

  u = (*pos);
  my_putstr("\33[2K\r");
  my_putstr(PS1);
  my_putstr((*s));
  (*pos) = my_strlen((*s));
  while ((*pos) > u)
    {
      if ((tigetstr("cub1") != (char *)-1))
	my_putstr(tigetstr("cub1"));
      (*pos) = (*pos) - 1;
    }
}

int	edit_buffer(int *pos, char *x, char **s)
{
  int       u;
  int       y;
  char      *save;

  y = 0;
  u = (*pos) - my_strlen(x);
  save = save_buffer(u, s);
  (*s) = my_realloc((*s), (my_strlen((*s)) + my_strlen(x) + 1));
  while (x[y] != 0)
    {
      (*s)[u] = x[y];
      y = y + 1;
      u = u + 1;
    }
  (*s)[u] = 0;
  (*s) = my_strcat((*s), save);
  free(save);
  reprint_new(s, pos);
  return (0);
}

int	add_to_buffer(int *pos, char **x, char **s)
{
  write(1, (*x), my_strlen((*x)));
  (*pos) = (*pos) + my_strlen((*x));
  if ((*pos) < my_strlen((*s)) + my_strlen((*x)))
    edit_buffer(pos, (*x), s);
  else
    {
      (*s) = my_realloc((*s), my_strlen((*s)) + my_strlen((*x)) + 1);
      (*s) = my_strcat((*s), (*x));
    }
  return (0);
}

char    *shell_gnl()
{
  int	pos;
  int   i;
  char  *s;
  char  *x;
  int	o;

  pos = 0;
  change_read(0);
  my_putstr(tigetstr("smkx"));
  s = my_strdup("");
  while (1)
    {
      x = get_next_line(0);
      if ((i = key_comparator(g_key, x)) != -1)
	{
	  if ((o = g_keybuiltins[i](&s, &pos)) == 1)
	    return (free_nquit(&x, s));
	  else if (o == 2)
	    return (free_nquit(&x, NULL));
	}
      else if (my_strlen(x) == 1)
	add_to_buffer(&pos, &x, &s);
      free(x);
    }
  return (s);
}
