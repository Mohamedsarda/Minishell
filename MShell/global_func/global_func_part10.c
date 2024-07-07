/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_func_part10.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:40:44 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:40:45 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*test(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	dst = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dst)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
	free(s1);
	return (dst);
}

int	ft_strlen_space(t_words *words)
{
	char	**dst;
	int		i;

	i = 0;
	multiple(&words->word, 0);
	dst = ft_split(words->word, ' ');
	if (!dst)
		return (0);
	while (dst[i])
		i++;
	free_split(dst);
	multiple(&words->word, 0);
	return (i);
}

int	handle_is_condition(t_words *head)
{
	if (head->is == 1)
		return (1);
	else
		return (ft_strlen_space(head));
}

int	ft_words(t_words *head)
{
	int	i;

	i = 0;
	while (head && hundle_error(head) != 0)
	{
		if (head->type == PIPE)
			return (i);
		if (head->type == HERD)
		{
			if (head)
				head = head->next;
			if (head)
				head = head->next;
			continue ;
		}
		if (head->type == 6 && head->word[0] != '\0')
			i += handle_is_condition(head);
		else if (head->type == 6 && head->word[0] == '\0' && head->is)
			i++;
		else
			i++;
		if (head)
			head = head->next;
	}
	return (i);
}

int	check_double_qout(char *str)
{
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
			return (1);
		str++;
	}
	return (0);
}
