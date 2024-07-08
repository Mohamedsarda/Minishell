/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:42:11 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:42:12 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

void	ft_sighandler(int i)
{
	(void)i;
	rl_catch_signals = 0;
	if (wait(NULL) != -1)
		return ;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit = 1;
}

int	quotes(char *str)
{
	int	a;
	int	b;
	int	i;

	a = 0;
	b = 0;
	i = 0;
	while (*str && str[i])
	{
		if (str[i] == '\"')
			a++;
		if (str[i] == '\'')
			b++;
		i++;
	}
	if (a % 2 != 0 || b % 2 != 0)
		return (0);
	else
		return (1);
}

static void	ft_minishell(t_env **env_stack, t_words **words, char *string)
{
	char	*str_sp;
	t_joins	*tmp;

	str_sp = ft_parsing(string);
	str_sp = back_to_string(str_sp);
	add_struct(str_sp, words, *env_stack);
	free(str_sp);
	tmp = ft_parse_stack(words, env_stack);
	ft_lstclear_joins(&tmp);
}

static void	ft_read_line(t_env **env_stack, t_words **words)
{
	char	*string;

	while (1)
	{
		string = readline("Minishell$ ");
		string = ft_strtrim(string, " ");
		if (g_exit)
		{
			g_exit = 0;
			ft_exit_status(env_stack, "1");
		}
		ft_string_nul(string, env_stack);
		if (!string[0] || ft_is_space(string))
		{
			free(string);
			continue ;
		}
		if (string[0] != '\0')
			add_history(string);
		multiple(&string, 0);
		if (check_qoutes(string) == 1)
			continue ;
		ft_minishell(env_stack, words, string);
	}
}

int	main(int ac, char **ar, char **env)
{
	t_words	*words;
	t_env	*env_stack;

	(void)ar;
	if (ac != 1)
		return (1);
	words = NULL;
	signal(SIGINT, ft_sighandler);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	(void)env_stack;
	env_stack = ft_create_env_stack(env, 0);
	ft_read_line(&env_stack, &words);
	ft_lstclear_env(&env_stack);
	rl_clear_history();
	return (0);
}
