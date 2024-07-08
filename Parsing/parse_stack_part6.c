/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stack_part6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:41:39 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:41:40 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unlink_free(char *str)
{
	unlink(str);
	signal(SIGINT, ft_sighandler);
	free(str);
}

int	run_pipes(t_joins	**stack_2, t_env **env)
{
	t_joins	*tmp;
	int		is;

	tmp = (*stack_2);
	is = 0;
	while (tmp)
	{
		is = 0;
		if (!tmp->content && tmp->out == 1 && tmp->in == 0)
			is = 1;
		tmp = tmp->next;
	}
	if (is)
		return (ft_lstclear_joins(stack_2), 1);
	ft_is_pipe(stack_2, env);
	return (0);
}

int	run_all_com(t_joins	**stack_2, t_env **env)
{
	t_joins	*tmp;

	tmp = (*stack_2);
	if (tmp && !tmp->next)
	{
		if (tmp->content != NULL)
			ft_run_commad(stack_2, env, tmp->content[0]);
	}
	else
		if (run_pipes(stack_2, env) == 1)
			return (1);
	return (0);
}

int	ft_ctr_c_check(t_joins *head)
{
	if (!head)
		return (-1);
	while (head)
	{
		if (head->in == -5)
			return (1);
		head = head->next;
	}
	return (0);
}

int	ft_check_error(t_joins **stack_2, t_joins *new,
		t_words **words, t_env **env)
{
	if (hundle_error((*words)) == 0 || new->in == -5)
	{
		if (new->in == -5)
			ft_exit_status(env, "1");
		return (ft_lstclear(words), ft_lstclear_joins(stack_2), 0);
	}
	return (1);
}
