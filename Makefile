##
## Makefile for Makefile in /home/alkoleek/PSU_2016_minishell1
## 
## Made by Maxime DROUIN
## Login   <alkoleek@epitech.net>
## 
## Started on  Fri Jan 20 02:27:55 2017 Maxime DROUIN
## Last update Mon May 15 18:12:30 2017 Laroche Achille
##

CC	=	gcc -I ./include/

LDFLAGS	=	-Llib -lgnl -lmy -lncurses

CFLAGS +=	-Wextra -Wall -Werror

RM	=	rm -f

NAME	=	42sh

SRCS	=	tools.c			\
		my_cd.c			\
		parse_cmd.c		\
		exec.c			\
		env_cmd.c		\
		m2_llist.c		\
		m2_cmdfill.c		\
		m2_exec.c		\
		m2_redirection.c	\
		m2_redirector.c		\
		m2_parser_1.c		\
		m2_parser_2.c		\
		m2_builtins.c		\
		m2_builtins_2.c		\
		m2_builtins_3.c		\
		m2_builtins_exec.c	\
		m2_waiters.c		\
		init_shell.c		\
		alias_loader.c		\
		alias_func.c		\
		alias_func_2.c		\
		fill_list.c		\
		comparator.c		\
		key_catch.c		\
		readline.c		\
		autocomp.c		\
		autocomp_tools.c	\
		line_editing.c		\
		key_builtin.c	        \
		key_builtin_2.c		\
		history.c		\
		main.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./lib/libgnl
	make -C ./lib/libmy
	$(CC) $(SRCS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)
	make clean -C ./lib/libgnl
	make clean -C ./lib/libmy

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./lib/libgnl
	make fclean -C ./lib/libmy

re : fclean all

.PHONY: all clean fclean re
