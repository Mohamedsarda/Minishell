/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_part1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:39:41 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:39:42 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	check_nmbr(char *str)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] != '\0' || i == 0)
		return (1);
	return (0);
}

void	ft_more_args(char	*str, t_env **env)
{
	if (check_nmbr(str) || ft_atoi_checker(str) == 255 || ft_space(str))
	{
		ft_putstr("Minishell$: exit: numeric argument required\n", 2);
		ft_exit_status(env, "255");
		exit(255);
	}
	else
	{
		ft_putstr("Minishell$: exit: too many arguments\n", 2);
		ft_exit_status(env, "1");
		return ;
	}
}
