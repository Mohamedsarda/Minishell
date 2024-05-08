#include "../minishell.h"

int	ft_strlen_key(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

char	*befor_equal(char	*str)
{
	char	*key;
	int		i;

	i = 0;
	key = malloc(ft_strlen_key(str) + 1);
	if(!key)
		return (NULL);
	while(*str != '=')
	{
		key[i] = *str;
		str++;
		i++;
	}
	key[i] = '\0';
	return (key);
}

int	ft_strlen_value(char *str)
{
	int i;

	i = 0;
	while(*str != '=')
		str++;
	while(str[i])
		i++;
	return (i);
}

char	*after_equal(char	*str)
{
	char	*key;
	int		i;

	i = 0;
	key = malloc(ft_strlen_value(str) + 1);
	if(!key)
		return (NULL);
	while(*str != '=')
		str++;
	str++;
	while(*str)
	{
		key[i] = *str;
		str++;
		i++;
	}
	key[i] = '\0';
	return (key);
}

void    ft_export(t_joins **head, t_env *env)
{
	char	*command;
	char	*key;
	char	*value;
	t_env *node = env;
	int		i;

	i = 1;
	while((*head)->content[i])
	{
		command = ft_strdup((*head)->content[i]);
		key = befor_equal(command);
		value = after_equal(command);
		node = ft_lstnew_env(key, value);
		ft_lstadd_back_env(&env, node);
		i++;
	}
	free(command);
	free(key);
	free(value);
	ft_lstclear_joins(head);
}