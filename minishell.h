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
	struct s_env	*next;
}	t_env;

int		ft_strlen_str_sp(char *str);
char	*ft_parsing(char *str);
void	add_struct(char *str, t_words **words);
int		hundle_error(t_words *words);
t_words	*ft_lstnew(char *content);
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
t_joins	*ft_parse_stack(t_words **words);
char	*ft_strjoin(char *s1, char *s2);
//env
t_env	*ft_create_env_stack(char **env);
char	*ft_strdup(char *s1);
t_env	*ft_lstnew_env(char *val_1, char *val_2);
void	ft_lstadd_back_env(t_env **head, t_env *node);
void	ft_sighandler(int i);

#endif