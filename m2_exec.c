/*
** m2_exec.c for mysh in /home/alkoleek/PSU_2016_minishell2
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun Apr  9 14:36:12 2017 Maxime DROUIN
** Last update Sun Apr  9 14:36:12 2017 Maxime DROUIN
*/

#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"

int	(*g_wait_func[6])(char) = {exec_ifsuccess,
				   exec_iffailed,
				   no_wait_child,
				   full_wait_child,
				   full_wait_child,
				   full_wait_child};

int	child_executor(int pipefd[], t_llist list)
{
  if (signal(SIGINT, SIG_DFL) == SIG_ERR
      || signal(SIGTSTP, SIG_DFL) == SIG_ERR)
    exit(EXIT_FAILURE);
  close(pipefd[0]);
  if (list->type == 2)
    {
      if (dup2(pipefd[1], 1) == -1)
	exit(EXIT_FAILURE);
      close(pipefd[1]);
    }
  child_exec(list->prog_name, list->cmd);
  close(pipefd[1]);
  return (0);
}

void	parent_executor(int pipefd[])
{
  close(pipefd[1]);
  if (dup2(pipefd[0], 0) == -1)
    return ;
  close(pipefd[0]);
}

int	sub_exec_cmd(t_llist *list, int pipefd[])
{
  int	i;

  i = exec_builtin(list, pipefd);
  if (i == 1)
    {
      g_child_list = my_irealloc(g_child_list, g_child_count + 1);
      if ((g_child_list[g_child_count] = fork()) == 0)
	child_executor(pipefd, (*list));
      else
	parent_executor(pipefd);
      g_child_count = g_child_count + 1;
      return (0);
    }
  else
    parent_executor(pipefd);
  return (1);
}

int	wait_module(t_llist *list, char cmd_save)
{
  char	c;

  if (g_wait_func[(int)(*list)->type](cmd_save) == -1)
    {
      c = (*list)->type;
      while ((*list) != NULL && ((*list)->type == c
				 || (*list)->type == 2
				 || (*list)->type == 5))
	(*list) = del_first((*list));
    }
  if ((*list) == NULL)
    return (1);
  if ((*list)->type != 2)
    {
      free(g_child_list);
      g_child_list = NULL;
      g_child_count = 0;
    }
  return (0);
}

void	exec_cmd(t_llist list)
{
  char	cmd_save;
  int	pipefd[2];
  char	c;
  int	i;

  cmd_save = 5;
  g_child_count = 0;
  while (list != NULL)
    {
      if ((list = word_replace(list)) == NULL)
	return ;
      if (pipe(pipefd) == -1)
	{
	  my_puterr("Can't make pipe.\n");
	  wait_module(&list, cmd_save);
	  return ;
	}
      if ((i = sub_exec_cmd(&list, pipefd)) == 1)
	cmd_save = 5;
      c = list->type;
      if (wait_module(&list, cmd_save) == 0)
	list = del_first(list);
      cmd_save = c;
    }
}
