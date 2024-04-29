/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:45:18 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/04/29 13:25:25 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*arr;

	if ((int)count < 0 || (int)size < 0)
		return (NULL);
	arr = malloc(count * size);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, count * size);
	return (arr);
}
