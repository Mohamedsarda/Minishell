CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
SRCS	= ./Ft_libft/ft_strlen.c  ./Ft_libft/ft_lstadd_back_bonus.c \
			./Ft_libft/ft_lstnew_bonus.c ./Ft_libft/ft_split.c\
			./Parsing/parsing.c \
		main.c

OBJS	= $(SRCS:.c=.o)
NAME	= minishell

all: $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lreadline $(OBJS) -o $@

	
clean:
	$(RM) $(OBJS) $(OBJSB)

fclean: clean
	$(RM) $(NAME)
