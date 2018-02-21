/*
** minishell2_llist.c for mysh in /home/alkoleek/TEST_AREA/PSU_2016_minishell1
** 
** Made by Maxime DROUIN
** Login   <maxime.drouin@epitech.eu>
** 
** Started on  Sun Mar 26 22:34:18 2017 Maxime DROUIN
** Last update Sun Mar 26 22:34:18 2017 Maxime DROUIN
*/

#include <stdlib.h>
#include "my.h"

t_llist		add_last(t_llist list, char *cmd, char type)
{
  t_llist	new_list;
  t_llist	temp;
  static char	separator[3] = {' ', '\t', 0};

  temp = list;
  if ((new_list = malloc(sizeof(t_element))) == NULL)
    return (list);
  if ((new_list->cmd = parse_args(cmd, separator)) == NULL)
    return (list);
  new_list->prog_name = my_strdup(new_list->cmd[0]);
  if ((new_list->cmd[0] = clear_filename(new_list->cmd[0])) == NULL)
    return (list);
  new_list->type = type;
  new_list->nxt = NULL;
  if (list == NULL)
    return (new_list);
  else
    while (temp->nxt != NULL)
      temp = temp->nxt;
  temp->nxt = new_list;
  return (list);
}

t_llist		switch_to_last(t_llist list)
{
  t_llist	new;
  t_llist	temp;

  if (list->type == 2)
    return (list);
  temp = list;
  if ((new = malloc(sizeof(t_element))) == NULL)
    return (NULL);
  if ((new->cmd = tab_dup(list->cmd)) == NULL)
    return (NULL);
  new->nxt = NULL;
  new->type = list->type;
  new->prog_name = my_strdup(list->prog_name);
  while (temp->nxt != NULL)
    temp = temp->nxt;
  temp->nxt = new;
  return (list);
}

t_llist		del_first(t_llist list)
{
  t_llist	new_list;

  new_list = list->nxt;
  if (list != NULL)
    {
      free_2d(list->cmd);
      free(list->prog_name);
      free(list);
      return (new_list);
    }
  else
    return (NULL);
}

t_llist		add_end_cmd(t_llist list, char **temp)
{
  list = add_last(list, (*temp), 5);
  free((*temp));
  return (list);
}

t_llist		add_cmd_type(t_llist list, char **temp, char type, int *count_c)
{
  list = add_last(list, (*temp), type);
  free((*temp));
  (*temp) = NULL;
  (*count_c) = 0;
  return (list);
}
