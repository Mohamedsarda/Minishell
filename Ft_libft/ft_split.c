/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 02:12:46 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/04/29 13:21:18 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	check;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		check = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			check = 1;
			i++;
		}
		if (check == 1)
			count++;
	}
	return (count);
}

static void	ft_free(char **res, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(res[j]);
		j++;
	}
	free(res);
}

static char	**ft_loop( char *s, char **res, char c)
{
	char	*start;
	int		i;

	i = 0;
	while (*s)
	{
		start = s;
		if (*s != c)
		{
			while (*s != c && *s)
				s++;
			res[i] = ft_substr(start, 0, s - start);
			if (res[i] == NULL)
				return (ft_free (res, i), NULL);
			i++;
		}
		else
			s++;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char *s, char c)
{
	char	**res;
	int		worlds;

	if (s == NULL)
		return (NULL);
	worlds = count_words(s, c);
	res = malloc((worlds + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	return (ft_loop (s, res, c));
}
