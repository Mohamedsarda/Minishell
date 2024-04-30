/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medsarda <medsarda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 01:35:37 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/04/30 09:09:06 by medsarda         ###   ########.fr       */
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

t_words	*ft_lstnew(char *content)
{
	t_words	*new_node;

	new_node = NULL;
	new_node = (t_words *)malloc(sizeof(t_words));

	new_node->word = malloc(ft_strlen(content) + 1);
	// new_node->word = malloc(ft_strlen(content) + 1);
	if (!new_node || !new_node->word)
		return (NULL);
	ft_memcpy(new_node->word, content, ft_strlen(content));
	new_node->next = NULL;
	return (new_node);
}
