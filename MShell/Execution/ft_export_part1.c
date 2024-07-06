#include "../minishell.h"

static int	ft_strlen_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
			return (i);
		i++;
	}
	return (i);
}

static char	*befor_equal(char	*str)
{
	char	*key;
	int		i;

	i = 0;
	key = malloc(ft_strlen_key(str) + 1);
	if (!key)
		return (NULL);
	while (*str)
	{
		if (*str == '=')
			break ;
		if (*str == '+' && *(str + 1) == '=')
			break ;
		key[i] = *str;
		str++;
		i++;
	}
	key[i] = '\0';
	return (key);
}

static void	ft_print_error_export(t_env **env, int is, char *command)
{
	ft_exit_status(env, "1");
	if (is == 1)
		ft_putstr("Minishell$ export: `': not a valid identifier\n", 2);
	else if (is == 2)
	{
		ft_putstr("Minishell$ export: `", 2);
		ft_putstr(command, 2);
		ft_putstr("': not a valid identifier\n", 2);
	}
}

void	ft_export_extra(t_joins **head, t_env **env, int *i)
{
	char	*command;
	char	*value;
	char	*key;

	while ((*head)->content[++(*i)])
	{
		if (ft_strcmp((*head)->content[(*i)], "\"\"") == 0
			|| ft_strcmp((*head)->content[(*i)], "\'\'") == 0)
		{
			ft_print_error_export(env, 1, command);
			(*i)++;
			continue ;
		}
		command = ft_strdup((*head)->content[(*i)]);
		key = befor_equal(command);
		if (check_key_env(key) == 1)
			ft_print_error_export(env, 2, command);
		else
		{
			value = after_equal(command);
			send_to_stack_env(head, value, key, env);
		}
		free(command);
		free(key);
	}
}
