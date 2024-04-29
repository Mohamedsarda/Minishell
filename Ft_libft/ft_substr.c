/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:13:22 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/04/29 13:23:31 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*store(unsigned int start, char const *s, size_t len, char *str)
{
	size_t	i;

	i = 0;
	while (i < len && s[start] != '\0')
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	slen;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		str = ft_calloc(1, 1);
		if (str == NULL)
			return (NULL);
		return (str);
	}
	if (len > slen - start)
		len = slen - start;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	store (start, s, len, str);
	return (str);
}
