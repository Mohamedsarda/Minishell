/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:41:57 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:42:00 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_lstnew_env(char *val_1, char *val_2)
{
	t_env	*head;
	char	*t;

	t = val_2;
	head = (t_env *)malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	if (!t)
		head->equal = 0;
	else if (*t == '=')
	{
		t++;
		head->equal = 1;
	}
	else
		head->equal = 0;
	head->is = 0;
	head->key = ft_strdup(val_1);
	if (ft_strcmp(val_1, "_") == 0)
		head->value = ft_strdup("/usr/bin/env");
	else
		head->value = ft_strdup(t);
	head->print = 1;
	head->next = NULL;
	return (head);
}

t_joins	*ft_lstnew_joins(void)
{
	t_joins	*stack_2;

	stack_2 = (t_joins *)malloc(sizeof(t_joins));
	if (!stack_2)
		return (NULL);
	stack_2->in = 0;
	stack_2->out = 1;
	stack_2->error = 0;
	stack_2->quotes = 0;
	stack_2->content = NULL;
	stack_2->next = NULL;
	return (stack_2);
}
