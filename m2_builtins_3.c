/*
** m2_builtins_3.c for 42sh in /home/alkoleek/PSU_2016_42sh/bonus
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Wed May 17 22:53:34 2017 Maxime DROUIN
** Last update Wed May 17 22:53:34 2017 Maxime DROUIN
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

int     show_history()
{
  t_history     *temp;

  if (g_history != NULL)
    {
      temp = g_history->tail;
      while (temp != NULL)
	{
	  my_putstr("\t");
	  my_putnbr(temp->id);
	  my_putstr("\t");
	  my_putstr(temp->cmd);
	  my_putstr("\n");
	  temp = temp->prev;
	}
    }
  return (quit_builtin(EXIT_SUCCESS));
}

int     bui_show_history(t_llist *list, int pipefd[])
{
  if ((*list) == NULL)
    return (quit_builtin(EXIT_FAILURE));
  show_history();
  close(pipefd[1]);
  if (dup2(g_shell_env.fd_one, 1) == -1)
    return (quit_builtin(EXIT_FAILURE));
  return (quit_builtin(EXIT_SUCCESS));
}

int     bui_load_history(t_llist *list, int pipefd[])
{
  t_history     *temp;

  temp = g_history->head;
  while (temp != NULL)
    {
      if (my_getnbr((*list)->cmd[0] + 1) == temp->id)
	{
	  if (((*list) =
	       fill_list((*list), temp->cmd, g_delimiter, NULL)) == NULL)
	    return (quit_builtin(EXIT_FAILURE));
	  close(pipefd[1]);
	  if (dup2(g_shell_env.fd_one, 1) == -1)
	    return (quit_builtin(EXIT_FAILURE));
	  return (quit_builtin(EXIT_SUCCESS));
	}
      temp = temp->next;
    }
  my_puterr((*list)->cmd[0] + 1);
  my_puterr(": Event not found.\n");
  close(pipefd[1]);
  if (dup2(g_shell_env.fd_one, 1) == -1)
    return (quit_builtin(EXIT_FAILURE));
  return (quit_builtin(EXIT_FAILURE));
}

int     bui_history(t_llist *list, int pipefd[])
{
  if ((*list)->type == 2)
    if (dup2(pipefd[1], 1) == -1)
      return (quit_builtin(EXIT_FAILURE));
  if (my_strcmp((*list)->cmd[0], "history") == 0)
    return (bui_show_history(list, pipefd));
  else
    return (bui_load_history(list, pipefd));
  return (0);
}
