##
## Makefile for minishell2 in /home/Rubiks/PSU/PSU_2016_minishell2/lib
## 
## Made by Maxime BLANCHARD
## Login   <Rubiks@epitech.net>
## 
## Started on  Mon Mar 27 17:04:48 2017 Maxime BLANCHARD
## Last update Sun May  7 19:52:52 2017 Maxime BLANCHARD
##

RM      =       rm -f

NAME    =       ../libmy.a

SRCS    =       my_putchar.c         	\
                my_putstr.c             \
		my_putnbr.c		\
		my_showtab.c		\
                my_strlen.c             \
                my_strcmp.c             \
		my_strncmp.c		\
                my_strcat.c             \
		my_strdup.c		\
		my_strcpy.c		\
		my_realloc.c		\
		my_itoa.c		\
		my_str_isalpha.c	\
		tab_tools.c		\
		my_tabdup.c		\
		my_getnbr.c		\

OBJS    =       $(SRCS:.c=.o)

all:    $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
