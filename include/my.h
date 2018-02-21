/*
** my.h for my in /home/alkoleek/CPool_Day09/include
** 
** Made by Maxime DROUIN
** Login   <alkoleek@epitech.net>
** 
** Started on  Fri Oct 14 08:15:15 2016 Maxime DROUIN
** Last update Sun Jan 22 17:00:56 2017 Maxime DROUIN
*/

#ifndef MY_H_
# define MY_H_
# include <sys/types.h>
#ifndef O_LARGEFILE
#define O_LARGEFILE 0
#define READ_SIZE 1024
#endif
#define PS1 "\033[31;1m42sh\033[31;1m> \033[0m"
typedef struct          s_history
{
  char                  *cmd;
  int			id;
  struct s_history      *prev;
  struct s_history      *next;
}                       t_history;

typedef struct  s_dlist
{
  size_t        length;
  t_history     *tail;
  t_history     *head;
}               t_dlist;
typedef struct  s_alias
{
  char  *initial;
  char	**replace;
  struct s_alias *nxt;
}               t_alias;
typedef t_alias *t_alias_list;
typedef struct	s_element
{
  char	*prog_name;
  char	**cmd;
  char	type;
  struct s_element *nxt;
}		t_element;
typedef t_element  *t_llist;
typedef struct	s_shell_env
{
  int	  pgid;
  int     last_ret;
  int     fd_zero;
  int     fd_one;
  int     status;
  int	  tty;
}		t_shell_env;
extern	int	g_history_c;
extern	t_dlist	*g_history;
extern	t_shell_env	g_shell_env;
extern	char	**environ;
extern	int	*g_child_list;
extern	int	g_child_count;
extern	t_alias_list	g_alias;
extern  char	*g_delimiter[6];
extern	char	**g_key;
extern	char	*g_builtins_name[10];
void	free_history(t_dlist *);
int	new_history(char **, int *);
void    special_backspace(char **, int *, int);
void	normal_backspace(char **, int *, int, int);
int	key_comparator(char **, char *);
char	*free_nquit(char **, char *);
int	change_read(int);
void	show_answer(char **, char *);
char	*extract_path(char *);
char	*get_current_word(char *, int *);
void	autocmp_file(char *, char **, int *);
void    autocmp_cmd(char *, char **, int *);
int	check_dup_autocomp(char *, char **);
char	**base_cmd_compl(int *, char *);
int	kbui_move_l(char **, int *);
int     kbui_move_r(char **, int *);
int     kbui_history_u(char **, int *);
int     kbui_history_d(char **, int *);
int     kbui_backspace(char **, int *);
int     kbui_eol(char **, int *);
int     kbui_cariage(char **, int *);
int     kbui_autocmp(char **, int *);
int	add_to_buffer(int *, char **, char **);
void	dlist_display(t_dlist *);
int	show_history();
int	save_history(char *);
t_dlist	*add_history(t_dlist *, char *);
t_dlist *load_history(char *);
char	*shell_gnl();
int	builtin_selector(t_llist *);
int	init_shell();
char	*fill_buffer(char *, int *, char);
char	*q_mark(char *, char *, int *, int *);
void	init_fill_tab(int *, int *, int *, char **);
int	alias_loop();
int	comp_delimiter_2(char *, char **, int *);
void	reprint_new(char **, int *);
t_alias_list del_alias(t_alias_list);
char	**get_path();
void	free_alias(t_alias_list);
void	free_2d(char **);
int	*my_irealloc(int *, int);
int	check_alias(char **);
void	show_alias(t_alias_list);
t_alias_list	add_next_alias(t_alias_list, char **, char *);
t_alias_list	delete_alias(t_alias_list, int);
int	test_fds();
char	**tab_cat(char **, char **, int);
int	replace_alias(t_llist , t_alias_list, t_alias_list, int);
char	**put_on_bottom(char **, int, int);
int	tab_len(char **);
char	**tab_realloc(char **, int);
t_alias_list	load_alias_file(char *);
int	init_shell_env();
t_llist	word_replace(t_llist);
char	*my_strcat(char *, char *);
t_llist	add_last(t_llist, char *, char);
char	*my_itoa(int);
int	full_wait_child(char);
int	quit_builtin(int);
int	my_strncmp(char *, char *, int);
void	show_list(t_llist);
int	correct_cmd(t_llist);
char	**default_key();
int	count_cmd(t_llist);
void	exec_cmd(t_llist);
int	append_tofile(char **, int);
int	trunc_tofile(char **, int);
int	get_fromfile(char **, int);
int	get_fromuser(char **, int);
int	my_getnbr(char *);
t_llist	add_end_cmd(t_llist, char **);
int	my_cd(char **);
t_llist	switch_to_last(t_llist);
void	my_puterr(char *);
int	p_env();
int	redirect_tofile(char **);
void	put_oldpwd();
void	my_showtab(char **);
void	my_putnbr(int);
void	my_putchar(char);
void	signal_error(int);
void	my_putstr(char *);
char	*my_strdup(const char *);
int	my_str_isalpha(char *);
int	my_strlen(char *);
void	show_list(t_llist);
char	*my_strcpy(char *, char *);
t_llist  del_first(t_llist);
int	exec();
int	child_exec(char *, char **);
int	find_and_exec(char **);
int	p_end(char ***);
void	end_add(char *, char *);
int	set_env(char *, char *);
int	unset_env(char *);
char	*env_modify(char *, char *);
int	environ_count();
int	env_nb(const char *);
char	*get_env(const char *);
void	signal_handler(int);
char	**parse_args(char *, char *);
char	*path_cmd(char *, char *);
int	my_strcmp(char *, char *);
int	is_relative(char *);
int	exec_builtin(t_llist *, int[]);
char	*get_next_line(int);
int	line_check(char *);
t_llist	fill_list(t_llist, char *, char **, char *);
char	*my_realloc(char *, int);
int	comp_delimiter(char, char *);
int	count_args(char *, char *);
t_llist	add_cmd_type(t_llist, char **, char, int *);
char	*clear_filename(char *);
char	**tab_dup(char **);
int	bui_cd(t_llist *, int *);
int     bui_exit(t_llist *, int *);
int     bui_setenv(t_llist *, int *);
int     bui_unsetenv(t_llist *, int *);
int     bui_env(t_llist *, int *);
int	bui_echo(t_llist *, int *);
int	bui_alias(t_llist *, int *);
int	bui_unalias(t_llist *, int *);
int     bui_history(t_llist *, int *);
int	full_wait_child(char);
int	no_wait_child(char);
int	exec_iffailed(char);
int	exec_ifsuccess(char);
#endif
