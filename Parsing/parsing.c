/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:50:50 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/04/29 13:36:36 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_str_sp(char *str)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (str[a])
	{
		if (str[a] == '|' || str[a] == '>'
			|| str[a] == '<')
		{
			if (str[a - 1] != ' ')
				i++;
			if (str[a + 1] != ' ')
				i++;
		}
		a++;
		i++;
	}
	return (i);
}

char	*ft_parsing(char *str)
{
	char	*str_sp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str_sp = malloc(ft_strlen_str_sp(str) + 1);
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '>'
			|| str[i] == '<')
			if (str[i - 1] != ' ')
				str_sp[j++] = ' ';
		str_sp[j] = str[i];
		j++;
		if (str[i] == '|' || str[i] == '>'
			|| str[i] == '<')
			if (str[i + 1] != ' ')
				str_sp[j++] = ' ';
		i++;
	}
	str_sp[j] = '\0';
	return (str_sp);
}

// 
// static int	ft_add(t_words **head, char *a)
// {
// 	t_words	*node;

// 	node = ft_lstnew(a);
// 	ft_lstadd_back(head, node);
// 	return (0);
// }



void	add_struct(char *str, t_words **words)
{
	char	**tmp;
	int		j;

	j = -1;
	tmp = ft_split(str, ' ');
	if (tmp == NULL || *tmp == NULL)
		return ;
	printf("%s\n", *tmp);
	// while (tmp[++j])
	// 	ft_add(words, tmp[j]);
}