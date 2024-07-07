/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_func_part11.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:40:46 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:40:47 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	check_if_export(t_words **head, char *content)
{
	t_words	*a;

	if (head == NULL)
		return (6);
	a = *head;
	while (a)
	{
		if (!ft_strcmp(a->word, "export") && ft_strchr(content, '=') == 1)
			return (0);
		a = a->next;
	}
	return (6);
}

int	ft_check_type(t_words **head, char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (check_if_export(head, content) == 0)
				return (0);
			return (6);
		}
		i++;
	}
	if (*content == '>' && *(content + 1) == '>')
		return (5);
	else if (*content == '<' && *(content + 1) == '<')
		return (4);
	else if (*content == '>')
		return (2);
	else if (*content == '<')
		return (1);
	else if (*content == '|')
		return (3);
	else
		return (0);
}

void	ft_creat_list_no_herd(t_words *head, char **dst, int *i)
{
	char	**str;
	int		j;

	j = 0;
	if (head->is == 1)
	{
		dst[(*i)++] = ft_strdup(head->word);
		head = head->next;
		return ;
	}
	multiple(&head->word, 0);
	str = ft_split(head->word, ' ');
	if (!str)
		return ;
	while (str[j])
	{
		multiple(&str[j], 0);
		dst[(*i)++] = ft_strdup(str[j++]);
	}
	multiple(&head->word, 0);
	free_split(str);
}

void	ft_open_red(int is, t_joins *tmp, int *i, t_words *words)
{
	if (is == 1)
	{
		if (tmp->out > 1)
			close(tmp->out);
		tmp->out = open(tmp->content[++(*i)], O_CREAT
				| O_TRUNC | O_WRONLY, 0644);
	}
	else if (is == 2)
	{
		if (tmp->in > 0)
			close(tmp->in);
		tmp->in = open(tmp->content[++(*i)], O_RDONLY, 0644);
	}
	else if (is == 3)
	{
		if (tmp->out > 1)
			close(tmp->out);
		tmp->out = open(tmp->content[++(*i)], O_CREAT
				| O_RDWR | O_APPEND, 0644);
	}
	if (words)
		words = words->next;
}
