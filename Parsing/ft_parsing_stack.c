/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medsarda <medsarda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:22:33 by msarda            #+#    #+#             */
/*   Updated: 2024/04/30 09:48:03 by medsarda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_words *ft_parse_stack(t_words **words)
{
	t_words *head;
	t_words *head_2;

	head = *words;
	head_2 = NULL;
	while (head)
	{
		printf("[%s]\n", head->word);
		// if (head->type == 0)
		// 	ft_lstadd_back(&head_2, head);
	// 	// else if (head->type == 2)
	// 	// {
	// 	// 	ft_lstadd_back(&head_2, head);
	// 	// 	ft_lstadd_back(&head_2, head->next);
	// 	// }
		head = head->next;
	}
	ft_lstclear(words);
	return (head_2);
}