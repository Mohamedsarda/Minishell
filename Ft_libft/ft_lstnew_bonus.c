/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 01:35:37 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/04/29 13:18:46 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_words	*ft_lstnew(char *content)
{
	t_words	*new_node;

	new_node = NULL;
	new_node = (t_words *)malloc(sizeof(t_words));
	if (!new_node)
		return (NULL);
	new_node->word = content;
	new_node->next = NULL;
	return (new_node);
}
