/*
** autocomp.c for 42sh in /home/alkoleek/PSU_2016_42sh
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun May 21 10:48:20 2017 Maxime DROUIN
** Last update Sun May 21 10:48:20 2017 Maxime DROUIN
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

char		**cmd_find(char **answer, char **path, char *str, int *x)
{
  int		i;
  DIR		*rep;
  struct dirent *file;

  i = 0;
  while (path[i] != 0)
    {
      rep = opendir(path[i]);
      if (rep != NULL)
	{
	  while ((file = readdir(rep)) != NULL)
	    if (my_strncmp(file->d_name, str, my_strlen(str)) == 0
		&& check_dup_autocomp(file->d_name + my_strlen(str), answer))
	      {
		answer = tab_realloc(answer, (*x) + 1);
		answer[(*x)] = my_strdup(file->d_name + my_strlen(str));
		(*x) = (*x) + 1;
	      }
	  closedir(rep);
	}
      i = i + 1;
    }
  return (answer);
}

char		**file_find(char **answer, char *str, char *path, int *x)
{
  DIR		*rep;
  struct dirent	*file;
  char		*filepath;

  rep = opendir(path);
  if (rep != NULL)
    {
      while ((file = readdir(rep)) != NULL)
	if ((my_strncmp(file->d_name, str, my_strlen(str)) == 0
	     && check_dup_autocomp(file->d_name + my_strlen(str), answer)
	     && access((filepath = path_cmd(path, file->d_name)), F_OK) == 0))
	  {
	    answer = tab_realloc(answer, (*x) + 1);
	    answer[(*x)] = my_strdup(file->d_name + my_strlen(str));
	    (*x) = (*x) + 1;
	    free(filepath);
	  }
      closedir(rep);
    }
  return (answer);
}

void	autocmp_cmd(char *str, char **s, int *pos)
{
  char	**path;
  char	**answer;
  char	*space;
  int	x;

  x = 0;
  answer = base_cmd_compl(&x, str);
  if ((path = parse_args(getenv("PATH"), ":\0")) == NULL)
    path = get_path();
  answer = cmd_find(answer, path, str, &x);
  if (x == 1)
    {
      space = my_strdup(" ");
      add_to_buffer(pos, &answer[0], s);
      if ((*s)[(*pos)] != ' ' && (*s)[(*pos)] != 0)
	add_to_buffer(pos, &space, s);
      free(space);
    }
  else if (x != 0)
    {
      show_answer(answer, str);
      reprint_new(s, pos);
    }
  free_2d(path);
  free_2d(answer);
}

void		autocmp_file(char *str, char **s, int *pos)
{
  char		**answer;
  char		*path;
  static char	*space = " ";
  int		x;

  x = 0;
  path = extract_path(str);
  if (!is_relative(str))
    str = str + my_strlen(path);
  answer = NULL;
  answer = file_find(answer, str, path, &x);
  if (x == 1)
    {
      add_to_buffer(pos, &answer[0], s);
      if ((*s)[(*pos)] != ' ' && (*s)[(*pos)] != 0)
	add_to_buffer(pos, &space, s);
    }
  else if (x != 0)
    {
      show_answer(answer, str);
      reprint_new(s, pos);
    }
  free(path);
  free_2d(answer);
}
