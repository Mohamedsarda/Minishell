/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medsarda <medsarda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:07:26 by eel-ghal          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/30 12:50:47 by medsarda         ###   ########.fr       */
=======
/*   Updated: 2024/04/30 13:09:38 by eel-ghal         ###   ########.fr       */
>>>>>>> eel-ghal
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
	t_joins *tmp;
	char *string;

	words = NULL;
	(void)tmp;
	signal(SIGINT, ft_sighandler);
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
<<<<<<< HEAD
		tmp = ft_parse_stack(&words);
		// t_words *test = tmp;
		// while (test)
		// {
		// 	printf("[%s] ", test->word);
		// 	test = test->next;
		// }
=======
		t_words *a = words;
		while (a)
		{
			printf("%s | %d\n", a->word, a->type);
			a = a->next;
		}
>>>>>>> eel-ghal
	}
	return (0);
}