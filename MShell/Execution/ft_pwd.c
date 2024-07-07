/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:40:10 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:40:11 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_pwd(t_joins	**stack_2, int is)
{
	char	buffer[1024];

	getcwd(buffer, sizeof(buffer));
	if (is)
		return (ft_strdup(buffer));
	else
	{
		ft_putstr(buffer, (*stack_2)->out);
		ft_putstr("\n", (*stack_2)->out);
	}
	return (NULL);
}
