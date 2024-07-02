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

void	multiple(char **str, int is)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str && *str && str[0][i])
	{
		if (is == 0 && str[0][i] == '\"')
		{
			i++;
			while (str[0][i] && str[0][i] != '\"')
			{
				str[0][i] *= -1;
				i++;
			}
		}
		else if (str[0][i] == '\'')
		{
			i++;
			while (str[0][i] && str[0][i] != '\'')
			{
				str[0][i] *= -1;
				i++;
			}
		}
		if (str[0][i] != '\0')
			i++;
	}
}

char	*back_to_string(char	*string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '\'')
		{
			multiple(&string, 0);
			return (string);
		}
		else if (string[i] == '\"')
		{
			multiple(&string, 0);
			return (string);
		}
		i++;
	}
	return (string);
}

static int	ft_sign(const char str)
{
	if (str == '-')
		return (-1);
	return (1);
}

int	ft_atoi4(const char *str)
{
	long int	nbr;
	long int	nb;
	int			sign;

	nbr = 0;
	sign = 1;
	while ((*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\v' || *str == '\f' || *str == '\r') && (str++));
	if (*str == '-' || *str == '+')
	{
		sign = ft_sign(*str);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nbr * 10 + (*str - '0');
		if (nbr > nb && sign == 1)
			return (-1);
		else if (nbr > nb && sign == -1)
			return (0);
		str++;
		nbr = nb;
	}
	return (nbr * sign);
}

void	ft_minishell(t_env **env_stack, t_words **words, char *string)
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

void	ft_read_line(t_env **env_stack, t_words **words)
{
	char	*string;
	t_env	*tmp;

	while (1)
	{
		string = readline("Minishell$ ");
		string = ft_strtrim(string, " ");
		if (g_exit)
			ft_exit_status(env_stack, "1");
		if (!string)
		{
			tmp = ft_get_status_pos(*env_stack, "?");
			exit(ft_atoi4(tmp->value));
		}
		else if (!string[0])
		{
			free(string);
			continue ;
		}
		if (string[0] != '\0')
			add_history(string);
		multiple(&string, 0);
		if (quotes(string) == 0)
		{
			ft_putstr("Minishell : unexpected EOF while looking for matching `\"'\n", 2);
			free(string);
			continue ;
		}
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
