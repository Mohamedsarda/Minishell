/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:41:55 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:41:56 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdel_env(t_env *lst)
{
	if (!lst)
		return ;
	free(lst->key);
	free(lst->value);
	free(lst);
}

void	ft_lstdel_joins(t_joins *lst)
{
	int	i;

	if (!lst)
		return ;
	i = 0;
	if (lst->in > 2)
		close(lst->in);
	if (lst->out > 2)
		close(lst->out);
	if (lst->content)
		while (lst && lst->content[i])
			free(lst->content[i++]);
	free(lst->content);
	free(lst);
}

void	ft_lstdelone(t_words *lst)
{
	if (!lst)
		return ;
	free(lst->word);
	free(lst);
}
