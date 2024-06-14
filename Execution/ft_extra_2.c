#include "../minishell.h"

char	*delete_eq(char *str)
{
	char	*value;
	char	*tmp;
	int		i;

	i = 0;
	tmp = str;
	value = malloc(ft_strlen(tmp));
	if (!value)
		return (NULL);
	tmp++;
	while (*tmp)
	{
		value[i] = *tmp;
		tmp++;
		i++;
	}
	value[i] = '\0';
	free(str);
	return (value);
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

int	check_key_env(char *key)
{
	if ((*key >= '0' && *key <= '9') || ft_strlen(key) == 0)
		return (1);
	while (*key)
	{
		if ((*key < 'a' || *key > 'z') && (*key < 'A' || *key > 'Z')
			&& (*key < '0' || *key > '9') && *key != '_')
			return (1);
		key++;
	}
	return (0);
}

int	ft_strlen_key(char *str)
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

void	ft_swap_env(t_env **a, t_env **b)
{
	t_env	*tmp;

	tmp = (*b);
	(*b) = (*a);
	(*a) = tmp;
}
