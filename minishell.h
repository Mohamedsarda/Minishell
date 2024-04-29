/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:07:32 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/04/29 13:36:30 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_words
{
	char			*word;
	char			*type;
	struct s_words	*next;
}	t_words;

int		ft_strlen_str_sp(char *str);


//split
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *dst, size_t n);
//


#endif