/*
** key_catch.c for 42sh in /home/alkoleek/PSU_2016_42sh/bonus
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Tue May 16 18:25:19 2017 Maxime DROUIN
** Last update Wed May 17 14:01:06 2017 Maxime BLANCHARD
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ncurses.h>
#include <getopt.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include "my.h"

int     change_read(int state)
{
  static struct termios old;
  struct termios        new;

  if (state == 0)
    {
      if (ioctl(0, TCGETS, &old) == -1 || ioctl(0, TCGETS, &new) == -1)
	return (1);
      new.c_lflag &= ~ECHO;
      new.c_lflag &= ~ICANON;
      new.c_cc[VMIN] = 1;
      new.c_cc[VTIME] = 1;
      if (ioctl(0, TCSETS, &new) == -1)
	return (1);
    }
  else
    if (ioctl(0, TCSETS, &old) == -1)
      return (1);
  return (0);
}

char    **default_key()
{
  char  **key;

  if ((key = malloc(sizeof(char *) * 9)) == NULL)
    return (NULL);
  if (((key[0] = tigetstr("kcub1")) == (char *)-1)
      || ((key[1] = tigetstr("kcuf1")) == (char *)-1)
      || ((key[2] = tigetstr("kcuu1")) == (char *)-1)
      || ((key[3] = tigetstr("kcud1")) == (char *)-1)
      || ((key[4] = tigetstr("kbs")) == (char *)-1)
      || ((key[5] = my_strdup("\04")) == NULL)
      || ((key[6] = my_strdup("")) == NULL)
      || ((key[7] = my_strdup("\t")) == NULL))
    return (NULL);
  key[8] = 0;
  return (key);
}

int     key_comparator(char **key, char *str)
{
  int   i;

  i = 0;
  while (key != NULL && key[i] != 0)
    {
      if (my_strcmp(key[i], str) == 0)
	return (i);
      i = i + 1;
    }
  return (-1);
}

int	check_dup_autocomp(char *str, char **answer)
{
  int	i;

  i = 0;
  while (answer != NULL && answer[i] != NULL)
    {
      if (my_strcmp(str, answer[i]) == 0)
	return (0);
      i = i + 1;
    }
  return (1);
}

void	show_answer(char **answer, char *str)
{
  int	i;

  i = 0;
  my_putstr("\n");
  while (str != NULL && answer != NULL && answer[i] != NULL)
    {
      my_putstr(str);
      my_putstr(answer[i]);
      my_putstr("\n");
      i = i + 1;
    }
}