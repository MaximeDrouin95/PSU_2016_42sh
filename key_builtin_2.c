/*
** key_builtin_2.c for 42sh in /home/alkoleek/PSU_2016_42sh
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun May 21 10:58:44 2017 Maxime DROUIN
** Last update Sun May 21 10:58:44 2017 Maxime DROUIN
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

int     kbui_eol(char **s, int *pos)
{
  change_read(1);
  my_putstr("\33[2K\r");
  my_putstr(PS1);
  my_putstr("exit\n");
  free((*s));
  free_alias(g_alias);
  free_history(g_history);
  (*pos) = 0;
  exit(g_shell_env.last_ret);
}

int     kbui_cariage(char **s, int *pos)
{
  change_read(1);
  my_putstr("\n");
  (*pos) = 0;
  if ((*s)[0] == 0)
    return (2);
  return (1);
}

int		kbui_history_d(char **s, int *pos)
{
  t_dlist       *history;
  t_history     *temp;
  int		i;

  i = 0;
  history = g_history;
  my_putstr("\33[2K\r");
  my_putstr(PS1);
  if (history != NULL)
    {
      temp = history->head;
      g_history_c = g_history_c - 1;
      if (g_history_c < 0)
	return (new_history(s, pos));
      while (temp->next != NULL && i < g_history_c)
	{
	  temp = temp->next;
	  i = i + 1;
	}
      my_putstr(temp->cmd);
      free((*s));
      (*s) = my_strdup(temp->cmd);
      (*pos) = my_strlen((*s));
    }
  return (0);
}

void		free_history(t_dlist *list)
{
  t_history     *temp;
  t_history     *del;

  if (list != NULL)
    {
      temp = list->head;
      while (temp != NULL)
	{
	  del = temp;
	  free(temp->cmd);
	  temp = temp->next;
	  free(del);
	}
      free(list);
    }
}

int	new_history(char **s, int *pos)
{
  free((*s));
  (*s) = my_strdup("");
  (*pos) = 0;
  return (0);
}
