/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:45:37 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/01/20 14:36:23 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*curr;
	int		i;

	i = 0;
	curr = lst;
	while (curr != NULL)
	{
		i++;
		curr = curr->next;
	}
	return (i);
}
