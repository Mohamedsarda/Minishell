/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:07:32 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/04/30 09:02:20 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <signal.h>

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

int		ft_strlen_str_sp(char *str);
char	*ft_parsing(char *str);
void	add_struct(char *str, t_words **words);

t_words	*ft_lstnew(char *content);
void	ft_lstadd_back(t_words **head, t_words *node);
size_t	ft_strlen(char *s);

//split
char	**ft_split(char const *s, char c);
void	ft_bzero(void *dst, size_t n);
void	ft_lstadd_back(t_words **head, t_words *node);
int	ft_strcmp(char *s1, char *s2);
//

#endif