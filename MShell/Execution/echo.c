/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:39:26 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:39:27 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_after_echo(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_putstr_n(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

static void	ft_print_echo(char **str, int fd, int *i)
{
	int	j;

	j = 1;
	while (str[j] && ft_strncmp(str[j], "-n", 2) == 0
		&& ft_check_after_echo(str[j]) != 0)
		j++;
	(*i) = j;
	while (str[(*i)])
	{
		ft_putstr_n(str[(*i)], fd);
		if (str[(*i) + 1])
			write(fd, " ", 1);
		(*i)++;
	}
}

void	ft_echo(t_joins **head, t_env **env)
{
	t_joins	*tmp;
	int		i;
	int		j;

	tmp = (*head);
	i = 1;
	ft_exit_status(env, "0");
	if (!tmp->content[i])
	{
		write(tmp->out, "\n", 1);
		return ;
	}
	j = 1;
	if (ft_strncmp(tmp->content[j], "-n", 2) == 0
		&& ft_check_after_echo(tmp->content[j]))
	{
		i++;
		ft_print_echo(tmp->content, tmp->out, &i);
	}
	else
	{
		ft_print_echo(tmp->content, tmp->out, &i);
		write(tmp->out, "\n", 1);
	}
}
