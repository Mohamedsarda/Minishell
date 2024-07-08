/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stack_part1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:41:19 by msarda            #+#    #+#             */
/*   Updated: 2024/07/08 23:56:49 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_for_syntax(t_words *head, t_env *env)
{
	if (ft_strcmp(head->word, "|") == 0)
	{
		printf ("Minishell : syntax error near unexpected token\n");
		ft_exit_status(&env, "258");
		return (1);
	}
	while (head)
	{
		if (hundle_error(head) == 0)
		{
			printf ("Minishell : syntax error near unexpected token\n");
			ft_exit_status(&env, "258");
			return (1);
		}
		head = head->next;
	}
	return (0);
}

static void	delete_qoutes_1(t_joins	**stack_2, char c)
{
	t_joins	*tmp;
	int		i;

	(void)c;
	if (!stack_2)
		return ;
	tmp = (*stack_2);
	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (check_double_qout(tmp->content[i]))
			{
				tmp->content[i] = dele_quotes(&tmp->content[i]);
				tmp->quotes = 1;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

char	**ft_create_list(t_joins *stack_2, t_words *head, t_env **env)
{
	char	**dst;
	int		words;

	words = ft_words(head);
	dst = (char **)malloc(sizeof (char *) * (words + 1));
	if (!dst)
		return (NULL);
	dst = ft_create_l_all(head, stack_2, env, dst);
	return (dst);
}

t_joins	*ft_store_stack(t_joins *stack_2, t_words **words, t_env **env)
{
	t_words	*head;
	t_joins	*new;

	head = (*words);
	stack_2 = ft_lstnew_joins();
	stack_2->content = ft_create_list(stack_2, *words, env);
	if (!ft_check_error(&stack_2, stack_2, words, env))
		return (NULL);
	while (head)
	{
		if (head->type == PIPE)
		{
			head = head->next;
			new = ft_lstnew_joins();
			new->content = ft_create_list(new, head, env);
			ft_lstaddback_joins(&stack_2, new);
			if (!ft_check_error(&stack_2, new, words, env))
				return (NULL);
			if (new && !new->content)
				return (stack_2);
		}
		else
			head = head->next;
	}
	return (stack_2);
}

t_joins	*ft_parse_stack(t_words **words, t_env **env)
{
	t_joins	*stack_2;
	int		syntax;

	stack_2 = NULL;
	if (!words || !env)
		return (NULL);
	syntax = ft_check_for_syntax(*words, *env);
	stack_2 = ft_store_stack(stack_2, words, env);
	if (syntax == 1 || ft_ctr_c_check(stack_2))
		return (ft_lstclear(words), stack_2);
	delete_qoutes_1(&stack_2, '\"');
	open_files(&stack_2, *words, *env);
	if (delete_check_error(words, stack_2) == 1)
		return (stack_2);
	if (run_all_com(&stack_2, env) == 1)
		return (NULL);
	return (stack_2);
}
