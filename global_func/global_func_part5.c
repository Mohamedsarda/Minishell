/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_func_part5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:40:29 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:40:30 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_words_counter(char const *str, char c)
{
	int	i;
	int	words;
	int	is_word;

	i = 0;
	words = 0;
	is_word = 0;
	while (str[i])
	{
		if (str[i] == c || str[i] == '\t')
			is_word = 0;
		else if (!is_word)
		{
			words++;
			is_word = 1;
		}
		i++;
	}
	return (words);
}

static int	ft_word_len(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != c && str[i] != '\t'))
		i++;
	return (i);
}

static void	*ft_free(char **arr, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
	return (NULL);
}

static char	**ft_putword(char const *str, char c, int words, char **dst)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	len = 0;
	while (i < words)
	{
		while (*str == c || *str == '\t')
			str++;
		len = ft_word_len(str, c);
		dst[i] = (char *)malloc(len * sizeof(char) + 1);
		if (!dst[i])
			return (ft_free(dst, i));
		j = 0;
		while (j < len)
			dst[i][j++] = *str++;
		dst[i][j] = '\0';
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		words;

	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '\0')
		return (NULL);
	words = ft_words_counter(s, c);
	dst = (char **)malloc((words + 1) * sizeof(char *));
	if (!dst)
		return (NULL);
	dst = ft_putword(s, c, words, dst);
	return (dst);
}
