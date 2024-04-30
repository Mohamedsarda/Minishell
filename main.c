/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medsarda <medsarda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:07:26 by eel-ghal          #+#    #+#             */
/*   Updated: 2024/04/30 09:48:07 by medsarda         ###   ########.fr       */
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
	t_words *tmp;
	char *string;

	words = NULL;
	(void)tmp;
	signal(SIGINT, ft_sighandler);
    rl_catch_signals = 0;
	while (1)
	{
		string = readline("minishell > ");
		if (!string)
			break ;
		// if(!hundle_error(string))
		// 	return 0;
		char *str_sp = ft_parsing(string);
		add_struct(str_sp, &words);
		tmp = ft_parse_stack(&words);
		// t_words *test = tmp;
		// while (test)
		// {
		// 	printf("[%s] ", test->word);
		// 	test = test->next;
		// }
	}
	return (0);
}