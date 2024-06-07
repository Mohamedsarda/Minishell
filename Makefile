CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
RM		= rm -rf
SRCS	= ./Ft_libft/ft_strlen.c  ./Ft_libft/ft_lstadd_back_bonus.c \
			./Ft_libft/ft_lstnew_bonus.c ./Ft_libft/ft_split.c\
			./Ft_libft/ft_lstclear.c \
			./Parsing/parsing.c ./Parsing/ft_parsing_stack.c ./Parsing/hundle_er.c \
			./Parsing/ft_env.c ./Parsing/ft_herd.c ./Parsing/ft_lst_joins.c \
			./Parsing/strlen_command.c ./Parsing/add_to_words.c ./Parsing/handle_enva.c\
			./Parsing/handle_enva_checker.c ./Parsing/handle_enva_qoutes_part2.c ./Parsing/parsi.c\
			./Parsing/handle_enva_qoutes_part1.c ./Parsing/utils_1.c ./Parsing/utils_2.c ./Parsing/utils_3.c\
			./Execution/ft_echo.c ./Execution/ft_pwd.c ./Execution/ft_env.c ./Execution/ft_cd.c\
			./Execution/ft_get_exe.c ./Execution/run.c ./Execution/ft_export.c ./Execution/ft_unset.c ./Execution/ft_exit.c\
			./Execution/ft_pipe.c\
			main.c

LDFLAGS  = "-L/Users/$(USER)/.brew/opt/readline/lib"
CPPFLAGS = "-I/Users/$(USER)/.brew/opt/readline/include"

OBJS	= $(SRCS:.c=.o)
NAME	= minishell

all: $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lreadline  $(LDFLAGS) $(CPPFLAGS) $(OBJS) -o $@

clean:
	$(RM) $(OBJS) $(OBJSB) ../.herd_file

fclean: clean
	$(RM) $(NAME)

re:fclean all
