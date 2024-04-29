/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:07:32 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/04/29 15:01:41 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_words
{
	char			*word;
	char			*type;
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
//

#endif