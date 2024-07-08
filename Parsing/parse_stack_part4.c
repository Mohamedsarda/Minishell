/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stack_part4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:41:31 by msarda            #+#    #+#             */
/*   Updated: 2024/07/09 00:13:58 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_free(char *str, int fd)
{
	int	j;

	j = -1;
	if (!str)
	{
		write(fd, "\n", 1);
		return ;
	}
	while (str[++j])
		write(fd, &str[j], 1);
	free(str);
	write(fd, "\n", 1);
}

void	ft_handle_error(t_env *env_stack, t_joins	*tmp)
{
	printf ("Minishell : ambiguous redirect\n");
	ft_exit_status(&env_stack, "1");
	free_split(tmp->content);
	tmp->content = NULL;
}

int	ft_fail_open(t_joins	*tmp, t_env *env_stack, int i)
{
	if (!tmp->error && (tmp->in == -1 || tmp->out == -1))
	{
		ft_putstr("Minishell$: ", 2);
		ft_putstr(tmp->content[i], 2);
		ft_putstr(" No such file or directory\n", 2);
		ft_exit_status(&env_stack, "1");
		free_split(tmp->content);
		tmp->content = NULL;
		return (1);
	}
	return (0);
}

void	ft_loop_con(t_env *env_stack, t_joins	*tmp, t_words **words)
{
	int		i;

	i = 0;
	while (tmp->content[i])
	{
		if (hundle_error((*words)) == 10)
		{
			ft_handle_error(env_stack, tmp);
			break ;
		}
		if (ft_strcmp(tmp->content[i], ">") == 0)
			ft_open_red(1, tmp, &i, words);
		else if (ft_strcmp(tmp->content[i], "<") == 0)
			ft_open_red(2, tmp, &i, words);
		else if (ft_strcmp(tmp->content[i], ">>") == 0)
			ft_open_red(3, tmp, &i, words);
		if (ft_fail_open(tmp, env_stack, i) == 1)
			break ;
		if ((*words))
			(*words) = (*words)->next;
		i++;
	}
}

void	open_files(t_joins **stack_2, t_words *words, t_env *env_stack)
{
	t_joins	*tmp;

	tmp = (*stack_2);
	while (tmp)
	{
		if (hundle_error(words) == 10)
			ft_handle_error(env_stack, tmp);
		else
			ft_loop_con(env_stack, tmp, &words);
		while (words && words->type != PIPE)
			words = words->next;
		if (words)
			words = words->next;
		if (tmp)
			tmp = tmp->next;
	}
}
