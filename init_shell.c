/*
** init_shell.c for init_shell in /home/alkoleek/PSU_2016_42sh
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sat Apr 22 20:10:22 2017 Maxime DROUIN
** Last update Sat Apr 22 20:10:22 2017 Maxime DROUIN
*/

#include <curses.h>
#include <ncurses.h>
#include <term.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"

char	**g_key;

int	init_env(char *name, char *value)
{
  if (name == NULL || value == NULL)
    return (-1);
  if (getenv(name) == NULL)
    {
      if (setenv(name, value, 1) == -1)
	my_puterr("Error: Cannot initialize environnement.\n");
    }
  return (0);
}

int	init_shell()
{
  if ((isatty(0)) == 1)
    {
      if (getenv("TERM") == NULL)
	setenv("TERM", "xterm-256color", 1);
      g_shell_env.tty = 1;
      setupterm(NULL, fileno(stdout), NULL);
      if ((g_key = default_key()) == NULL)
	return (-1);
    }
  return (0);
}
