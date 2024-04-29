/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 02:26:30 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/01/22 16:48:22 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push.h"

void	ft_lstadd_back(t_list **head, t_list *node)
{
	t_list	*last;

	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	if (!head || !node)
		return ;
	last = *head;
	while (last->next)
		last = last->next;
	last->next = node;
}
