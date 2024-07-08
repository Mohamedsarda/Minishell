/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_func_part8.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:40:38 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:40:39 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_length(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	if (i == 3)
		return (3);
	if (i != 2)
		return (0);
	return (1);
}

static int	check_space(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	while (str[i] && str[i] == c)
		i++;
	if (str[i])
		return (1);
	return (0);
}

static int	check_next_error(t_words *a)
{
	if (!a->next)
		return (0);
	if (a->next->is == 0 && a->next->type == 6
		&& check_space(a->next->word, ' ') == 1)
		return (10);
	else if (a->next->type == REDOU || a->next->type == REDIN
		|| a->next->type == PIPE || a->next->type == HERD
		|| a->next->type == APPEND || a->next->word == NULL)
		return (0);
	return (-1);
}

int	hundle_error(t_words *words)
{
	t_words	*a;
	int		len;

	a = words;
	if (a == NULL)
		return (1);
	len = check_length(a->word);
	if (((a->type == HERD || a->type == APPEND) && len >= 3))
		return (0);
	else if ((a->type == APPEND && len == 0) || (a->type == HERD && len == 0))
		return (0);
	if (a->type == REDOU || a->type == REDIN
		|| a->type == HERD || a->type == APPEND || a->word == NULL)
	{
		if (check_next_error(a) != -1)
			return (check_next_error(a));
	}
	if (a->type == PIPE)
	{
		if (!a->next)
			return (0);
		if (a->next->type == PIPE)
			return (0);
	}
	return (1);
}

int	check_key_env(char *key)
{
	if ((*key >= '0' && *key <= '9') || ft_strlen(key) == 0)
		return (1);
	while (*key)
	{
		if ((*key < 'a' || *key > 'z') && (*key < 'A' || *key > 'Z')
			&& (*key < '0' || *key > '9') && *key != '_')
			return (1);
		key++;
	}
	return (0);
}
