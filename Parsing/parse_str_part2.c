/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str_part2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:41:43 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:41:44 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_symbols(char *s, char *str, int *i)
{
	if (*str == '|')
	{
		if (s[0] != '|' || *i != 0)
			if (*(str - 1) != ' ')
				*i += 1;
		if (*(str + 1) != ' ')
			*i += 1;
	}
}

static void	check_redin_ou(char *str, int *i)
{
	if (*str == '>')
	{
		if (*i != 0)
			if (*(str - 1) != ' ' && *(str - 1) != '>')
				*i += 1;
		if (*(str + 1) != ' ' && *(str + 1) != '>')
			*i += 1;
	}
	else if (*str == '<')
	{
		if (*i != 0)
			if (*(str - 1) != ' ' && *(str + 1) != '<')
				*i += 1;
		if (*(str + 1) != ' ' && *(str + 1) != '<')
			*i += 1;
	}
}

int	ft_strlen_str_sp(char *str)
{
	int		i;
	char	*s;

	s = str;
	i = 0;
	while (str && *str)
	{
		if (*str == '|' || *str == '>' || *str == '<')
		{
			check_symbols(s, str, &i);
			check_redin_ou(str, &i);
		}
		str++;
		i++;
	}
	return (i);
}
