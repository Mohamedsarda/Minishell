/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 01:35:37 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/04/30 13:13:01 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
	*d = '\0';
	return (dest);
}

static int	ft_check_type(char *content)
{
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
	else if (*content == '$')
		return (6);
	else
		return (0);
}

t_words	*ft_lstnew(char *content)
{
	t_words	*new_node;

	new_node = NULL;
	new_node = (t_words *)malloc(sizeof(t_words));

	new_node->word = malloc(ft_strlen(content) + 1);
	new_node->type = ft_check_type(content);
	if (!new_node || !new_node->word)
		return (NULL);
	ft_memcpy(new_node->word, content, ft_strlen(content));
	new_node->next = NULL;
	return (new_node);
}
