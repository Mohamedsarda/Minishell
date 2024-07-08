/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:42:01 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:42:02 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env_size(t_env *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

void	ft_next_node_joins(t_joins **head)
{
	t_joins	*stack;
	int		i;

	stack = (*head)->next;
	i = 0;
	if ((*head)->in > 2)
		close((*head)->in);
	if ((*head)->out > 2)
		close((*head)->out);
	if ((*head)->content)
		while ((*head)->content[i])
			free((*head)->content[i++]);
	free((*head)->content);
	free((*head));
	(*head) = stack;
}
