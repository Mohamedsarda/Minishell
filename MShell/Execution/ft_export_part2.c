#include "../minishell.h"

static int	ft_strlen_value(char *str)
{
	int	i;

	i = 0;
	while (*str && *str != '=' && *str != '+')
		str++;
	while (str[i])
		i++;
	return (i);
}

char	*after_equal(char	*str)
{
	char	*value;
	int		i;

	i = 0;
	if (!*str)
		return (NULL);
	value = malloc(ft_strlen_value(str) + 1);
	if (!value)
		return (NULL);
	while (*str && *str != '=' && *str != '+')
		str++;
	while (*str)
	{
		value[i] = *str;
		str++;
		i++;
	}
	value[i] = '\0';
	return (value);
}

static int	check_value(char *value)
{
	if (!value)
		return (-1);
	if (*value == '+' && *(value + 1) == '=')
		return (2);
	if (*value == '=')
		return (1);
	return (-1);
}

int	check_key_in_path(char *key, t_env **env)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	send_to_stack_env(t_joins **head, char *value, char *key, t_env **env)
{
	t_env	*node;

	node = NULL;
	if (check_value(value) == 1)
		work_export(key, value, env, 0);
	else if (check_value(value) == 2)
		work_export(key, value, env, 2);
	else
	{
		if (check_key_in_path(key, env) == 1)
			return (free(value));
		if (ft_strcmp(key, "PWD") == 0 && value && !value[0])
		{
			free(value);
			value = ft_pwd(head, 1);
			node = ft_lstnew_env(key, value);
			node->equal = 1;
		}
		else
			node = ft_lstnew_env(key, value);
		free(value);
		ft_lstadd_back_env(env, node);
	}
}
