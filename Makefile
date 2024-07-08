CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
SRCS	= Execution/all_commands.c        Execution/run.c                 Parsing/struct_size.c	\
		Execution/echo.c                Parsing/creat_env_stack.c       Parsing/words_expan_dob.c	\
		Execution/ft_actions_pipe.c     Parsing/creat_env_stack_shlvl.c Parsing/words_handle_all.c	\
		Execution/ft_cd.c               Parsing/parse_stack_part1.c     global_func/global_func_part1.c	\
		Execution/ft_env.c              Parsing/parse_stack_part2.c     global_func/global_func_part2.c	\
		Execution/ft_exit.c             Parsing/parse_stack_part3.c     global_func/global_func_part3.c	\
		Execution/ft_exit_part1.c       Parsing/parse_stack_part4.c     global_func/global_func_part4.c	\
		Execution/ft_export.c           Parsing/parse_str_part1.c       global_func/global_func_part5.c	\
		Execution/ft_export_part1.c     Parsing/parse_str_part2.c       global_func/global_func_part6.c	\
		Execution/ft_export_part2.c     Parsing/store_words.c           global_func/global_func_part7.c	\
		Execution/ft_export_part3.c     Parsing/store_words_herd.c      global_func/global_func_part8.c	\
		Execution/ft_pipe.c             Parsing/struct_add_back.c       global_func/global_func_part9.c	\
		global_func/global_func_part10.c Execution/ft_pwd.c              Parsing/struct_clear.c	\
		global_func/global_func_part11.c Execution/ft_unset.c            Parsing/struct_new.c	\
		Parsing/struct_del.c	Parsing/parse_stack_part5.c		Parsing/parse_stack_part6.c			main.c \
		main_read.c

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
	$(RM) $(OBJS) $(OBJSB)

fclean: clean
	$(RM) $(NAME)

re:fclean all
