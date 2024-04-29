/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:07:26 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/04/29 14:16:49 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main()
{
	t_words *words;
	char *string;

	words = NULL;
	while (1)
	{
		// signal(SIGINT, ft_sighandler);
		string = readline("zaml > ");
		char *str_sp = ft_parsing(string);
		add_struct(str_sp, &words);
		t_words *a = words;
		while (a)
		{
			printf("%s\n", a->word);
			a =a->next;
		}
	}
	return (0);
}