/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:41:53 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:41:54 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstclear_env(t_env **lst)
{
	t_env	*cur;

	if (!lst)
		return ;
	while (*lst)
	{
		cur = *lst;
		*lst = (*lst)->next;
		ft_lstdel_env(cur);
	}
}

void	ft_lstclear_joins(t_joins **lst)
{
	t_joins	*cur;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		cur = *lst;
		*lst = (*lst)->next;
		if (cur)
			ft_lstdel_joins(cur);
	}
}

void	ft_lstclear(t_words **lst)
{
	t_words	*cur;

	if (!lst)
		return ;
	while (*lst)
	{
		cur = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(cur);
	}
}
