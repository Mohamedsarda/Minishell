/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-ghal <eel-ghal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:07:26 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/04/30 13:09:38 by eel-ghal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_sighandler(int i)
{
	(void)i;
    rl_catch_signals = 0;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    // rl_catch_signals = 1;
}

int main()
{
	t_words *words;
	char *string;

	words = NULL;
	rl_catch_signals = 0;
	while (1)
	{
		signal(SIGINT, ft_sighandler);
		string = readline("jjjj > ");
		if(!string)
			break;
		// if(!hundle_error(string))
		// 	return 0;
		char *str_sp = ft_parsing(string);
		add_struct(str_sp, &words);
		t_words *a = words;
		while (a)
		{
			printf("%s | %d\n", a->word, a->type);
			a = a->next;
		}
	}
	return (0);
}