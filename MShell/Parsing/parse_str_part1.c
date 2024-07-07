/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str_part1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:41:41 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:41:42 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_left_symbols(char **str, char **str_sp, int a)
{
	if (a != 0)
	{
		if (**str == '|' && *((*str) - 1) != ' ' && *((*str) - 1) != '\0')
		{
			**str_sp = ' ';
			(*str_sp)++;
		}
		else if (**str == '>' && *((*str) - 1) != ' '
			&& *((*str) - 1) != '\0' && *((*str) - 1) != '>')
		{
			**str_sp = ' ';
			(*str_sp)++;
		}
		else if (**str == '<' && *((*str) - 1) != ' '
			&& *((*str) - 1) != '\0' && *((*str) - 1) != '<')
		{
			**str_sp = ' ';
			(*str_sp)++;
		}
	}
}

static void	check_right_symbols(char **str, char **str_sp)
{
	if (**str == '|' && *((*str) + 1) != ' ' && *((*str) + 1) != '\0')
	{
		**str_sp = ' ';
		(*str_sp)++;
	}
	else if (**str == '>' && *((*str) + 1) != ' '
		&& *((*str) + 1) != '\0' && *((*str) + 1) != '>')
	{
		**str_sp = ' ';
		(*str_sp)++;
	}
	else if (**str == '<' && *((*str) + 1) != ' '
		&& *((*str) + 1) != '\0' && *((*str) + 1) != '<')
	{
		**str_sp = ' ';
		(*str_sp)++;
	}
}

char	*ft_parsing(char *str)
{
	char	*str_sp;
	char	*t;
	char	*s;
	int		a;

	s = str;
	a = 0;
	str_sp = malloc(ft_strlen_str_sp(str) + 1);
	if (!str_sp)
		return (NULL);
	t = str_sp;
	while (str && *str)
	{
		if (*str == '|' || *str == '>' || *str == '<')
			check_left_symbols(&str, &str_sp, a);
		((1) && (*str_sp = *str, a++, str_sp++));
		if (*str == '|' || *str == '>' || *str == '<')
		{
			check_right_symbols(&str, &str_sp);
		}
		str++;
	}
	*str_sp = '\0';
	free(s);
	return (t);
}

char	*back_to_string(char	*string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '\'')
		{
			multiple(&string, 0);
			return (string);
		}
		else if (string[i] == '\"')
		{
			multiple(&string, 0);
			return (string);
		}
		i++;
	}
	return (string);
}
