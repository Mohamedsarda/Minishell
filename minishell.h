#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <signal.h>
# include <fcntl.h>

# define WORD 0
# define REDIN 1 // <
# define REDOU 2 // >
# define PIPE 3 // |
# define HERD 4 // <<
# define APPEND 5 // >>
# define ENVV 6 // $

typedef struct s_words
{
	char			*word;
	int				type;
	int				is;
	struct s_words	*next;
}	t_words;

typedef struct s_joins
{
	char			**content;
	int				in;
	int				out;
	struct s_joins	*next;
}	t_joins;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				print;
	int				equal;
	struct s_env	*next;
}	t_env;

int		ft_strlen_str_sp(char *str);
char	*ft_parsing(char *str);
void	add_struct(char *str, t_words **words, t_env *env_stack);
int		hundle_error(t_words *words);
t_words	*ft_lstnew(char *content, t_env *env_stack);
void	ft_lstadd_back(t_words **head, t_words *node);
size_t	ft_strlen(char *s);

//split
char	**ft_split(char const *s, char c);
void	ft_bzero(void *dst, size_t n);
void	ft_lstadd_back(t_words **head, t_words *node);
int		ft_strcmp(char *s1, char *s2);
//
void	ft_lstclear(t_words **lst);
void	ft_lstdelone(t_words *lst);
t_joins	*ft_parse_stack(t_words **words, t_env **env);
char	*ft_strjoin(char *s1, char *s2);
//env
t_env	*ft_create_env_stack(char **env, int tmp);
char	*ft_strdup(char *s1);
t_env	*ft_lstnew_env(char *val_1, char *val_2);
void	ft_lstadd_back_env(t_env **head, t_env *node);
void	ft_sighandler(int i);
int		ft_get_env_len(char *str, char c);
char	*ft_strlcpy(char **str, int len);

char	*ft_strtrim(char *s1, char *set);
void	ft_putstr(char *str, int fd);
//
void	ft_lstclear_env(t_env **lst);
//
void	ft_lstclear_joins(t_joins **lst);
void	ft_herd_sig(int i);
void	ft_check_word_type(t_joins *stack_2, t_words **head,
			int *i, char **dst);
void	ft_handle_herd(t_joins *stack_2, t_words **head, t_env **env);
void	ft_next_node(t_words **head);
int		ft_stack_words(t_words *words);
//
t_joins	*ft_lstnew_joins(t_words **words);
void	ft_lstaddback_joins(t_joins **head, t_joins *node);
void	free_split(char **tmp);
char	**ft_create_list(t_joins *stack_2, t_words **head, t_env **env);

// strlen_command
int		ft_strlen_str_sp(char *str);
char	*handle_env(t_words *node, char *content, t_env *env);
void	multiple(char **str, int is);
int		quotes(char *str);
char	*ft_rm_quotes(char *string, char c);
//
void	ft_echo(t_joins **head);
void	ft_pwd(t_joins	**stack_2);
void	ft_next_node_joins(t_joins **head);
//
void	ft_env(t_env **env, t_joins **stack_2);
//
void	ft_cd(t_joins **head, t_env **env);
//
void	ft_run_commad(t_joins **head, t_env **env, char *type);
//
void    ft_export(t_joins **head, t_env **env);
//
void    ft_unset(t_joins **head, t_env **env);
//
void ft_exit(t_joins **head, t_env **env);
//handle_enva_checker.c
char	*check_env(char *str, t_env *env);
char	check_key(char c);
char	*cpy(char	*str, int len);
char	*atest(char *key, t_env *env, char *str);
//end handle_enva_checker.c

//handle_enva_qoutes_part1.c
char	*rm_single_qoutes(char *str);
int		check_double_qout(char *str);
char	*delete_double_qoutes(char *str);
char	*delete_qoutes(const char *str, char c);
char	*delete_all_double_qoutes(char *str);
//end handle_enva_qoutes_part1.c



//handle_enva_qoutes_part2.c
void	conv_all(char **str);
void	conv_all_pos(char **str);
void	convert_neg_to_po(char **str);
int		check_qoutes(char *str);
int		check_nig(char	*str);
//end handle_enva_qoutes_part2.c

//parsi.c
char	*test(char *s1, char *s2);
char	*add_one(char *s1, char s2);
int		ft_strlen_c(const char *str, char c);
void	multiple2(char **str);
//end parsi.c
void	ft_after_pipe(t_joins **head, t_env **env);

void    ft_run(t_joins **head, t_env **env);
void	env_equal(t_env **env);
//
void    ft_exit_status(t_env **env, char *status);
void	print_sorted_env(t_env **head);
#endif