#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <limits.h>

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
	int				error;
	int				quotes;
	struct s_joins	*next;
}	t_joins;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				print;
	int				equal;
	int				is;
	struct s_env	*next;
}	t_env;

void	ft_lstdel_env(t_env *lst);
void	ft_lstdel_joins(t_joins *lst);
void	ft_lstdelone(t_words *lst);

void	ft_lstclear_joins(t_joins **lst);
void	ft_lstclear(t_words **lst);
t_joins	*ft_lstnew_joins(void);
int		ft_check_error(t_joins **stack_2, t_joins *new,
			t_words **words, t_env **env);

void	ft_next_node_joins(t_joins **head);
int		ft_env_size(t_env *head);
void	ft_lstaddback_joins(t_joins **head, t_joins *node);
void	ft_lstadd_back(t_words **head, t_words *node);
//create_env_stack
t_env	*ft_create_env_stack(char **env, int tmp);
t_env	*ft_lstnew_env(char *val_1, char *val_2);
void	ft_lstadd_back_env(t_env **head, t_env *node);
void	ft_lstclear_env(t_env **lst);
//

//parsing_part1
char	*ft_parsing(char *str);
int		ft_strlen_str_sp(char *str);
//
char	*back_to_string(char	*string);
//
//split
char	**ft_split(char const *s, char c);
//

//global_func
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strlcpy(char **str, int len);
char	*ft_itoa(int n);
char	*ft_strtrim(char *s1, char *set);
t_env	*ft_get_status_pos(t_env *env, char *key);
int		ft_atoi4(const char *str);
void	multiple(char **str, int is);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_text_only(char *result, char *str, int *i);
void	ft_putstr(char *str, int fd);
void	ft_exit_status(t_env **env, char *status);
int		ft_strncmp(char *s1, char *s2, size_t n);
//
int		ft_check_type(t_words **head, char *content);
int		check_double_qout(char *str);
char	*test_1(char *s1, char *s2);
char	*get_only_key(char *str, int *i);
char	*check_env(char *str, t_env *env);
char	*ft_expand_in_double(char *result, char *str, int *i, t_env *env);

char	*dele_quotes(char **str);
int		hundle_error(t_words *words);

// parse_stack
t_joins	*ft_parse_stack(t_words **words, t_env **env);
char	**ft_create_l_all(t_words *head, t_joins *s2, t_env **env, char **dst);
void	free_split(char **tmp);

int		ft_words(t_words *head);
int		ft_herd_while(t_joins *stack_2, t_words *head, t_env **env);
void	ft_print_free(char *str, int fd);
void	ft_sighandler(int i);
void	ft_creat_list_no_herd(t_words *head, char **dst, int *i);
void	open_files(t_joins **stack_2, t_words *words, t_env *env_stack);
char	**ft_create_list(t_joins *stack_2, t_words *head, t_env **env);

//run
void	ft_run_commad(t_joins **head, t_env **env, char *type);
void	ft_cd(t_joins **head, t_env **env);
void	ft_echo(t_joins **head, t_env **env);
char	*ft_pwd(t_joins	**stack_2, int is);
void	ft_unset(t_joins **head, t_env **env);
void	ft_env(t_env **env_tmp, t_joins **stack_2);
void	ft_exit(t_joins **head, t_env **env, int fd);
void	ft_export(t_joins **head, t_env **env);
void	ft_run(t_joins **head, t_env **env);
//
int		ft_sign(char **str);
int		check_nmbr(char *str);
void	ft_more_args(char	*str, t_env **env);
int		ft_atoi_checker(char *str);
int		check_key_env(char *key);
char	*test(char *s1, char *s2);
void	ft_export_extra(t_joins **head, t_env **env, int *i);
char	*after_equal(char	*str);
void	send_to_stack_env(t_joins **head, char *value, char *key, t_env **env);
void	work_export(char *key, char *value, t_env **env, int is);
void	com_not_found(char *command);
void	ft_check_sig_fork(int status, t_env **env);
void	ft_change_status_fork(int status, t_env **env);
void	ft_check_run_norm_1(char **environ, char *command,
			t_joins **head, t_env **env);
char	**ft_create_env_from_stack(t_env *env);
void	ft_check_slash(char *command, t_env **env);
int		ft_atoi1(char *s);
void	ft_is_pipe(t_joins **head, t_env **env);
char	*handle_env(t_words *node, char *content, t_env *env);
int		check_key_in_path(char *key, t_env **env);
char	*ft_to_lower(char *str);
void	add_struct(char *str, t_words **words, t_env *env_stack);
char	*handle_single_parssing(char *result, char *str, int *i);
int		delete_check_error(t_words **words, t_joins *stack_2);
void	ft_open_red(int is, t_joins *tmp, int *i, t_words *words);
void	ft_handle_proc_child(t_joins **head, int *pipes,
			int *old, t_env **env);
void	ft_run_2(t_joins **head, t_env **env);
void	check_run_2(char **environ, char *command, t_joins **head, t_env **env);
void	ft_unlink_free(char *str);
int		check_qoutes(char *string);
void	ft_string_nul(char *string, t_env **env_stack);
int		quotes(char *str);
int		run_all_com(t_joins	**stack_2, t_env **env);
int		run_pipes(t_joins	**stack_2, t_env **env);
int		ft_space(char *str);
int		ft_env_size_hide(t_env *env);
int		ft_ctr_c_check(t_joins *head);
int		ft_is_space(char *str);
#endif