/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hundle_er.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:07:34 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/04/29 15:42:46 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	hundle_error(char *str)
{
	while (*str)
	{
		if(*str == '|')
		str++;
	}
	
}