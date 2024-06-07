#include "../minishell.h"

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

char	*befor_equal(char	*str)
{
	char	*key;
	int		i;

	i = 0;
	key = malloc(ft_strlen_key(str) + 1);
	if (!key)
		return (NULL);
	while (*str)
    {
        if(*str == '=')
            break;
        if(*str == '+' && *(str + 1) == '=')
            break;
        key[i] = *str;
        str++;
        i++;
    }
    key[i] = '\0';
    return (key);
}

int	ft_strlen_value(char *str)
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
	if(!*str)
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

int	ft_env_size(t_env *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
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
// export a; export a=; head has a= but he dont print it
void	print_sorted_env(t_env **head, t_joins **stack_2)
{
	int		count;
	t_env	*current;
	t_env	**arr;
	int		i;
	int		j;
	int		fd;

	current = (*head);
	if ((*stack_2)->out != 0 && (*stack_2)->in >= 0)
		fd = (*stack_2)->out;
	else
		fd = (*stack_2)->in;
	count = ft_env_size(current);
	arr = (t_env **)malloc(count * sizeof(t_env *));
	if (!arr)
		return ;
	i = 0;
	while (current)
	{
		arr[i++] = current;
		current = current->next;
	}
	i = -1;
	j = 0;
	while (++i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(arr[j]->key, arr[i]->key) < 0)
				ft_swap_env(&arr[j], &arr[i]);
			j++;
		}
	}
	i = -1;
	while (++i < count)
	{
		if (arr[i]->print)
		{
			ft_putstr("declare -x ", fd);
			ft_putstr(arr[i]->key, fd);
			if (arr[i]->equal)
				ft_putstr("=", fd);
			if (arr[i]->equal && ft_strlen(arr[i]->value) >= 0)
			{
				ft_putstr("\"", fd);
				ft_putstr(arr[i]->value, fd);
				ft_putstr("\"", fd);
			}
			ft_putstr("\n", fd);
		}
	}
	free(arr);
}

int	check_value(char *value)
{
	if(!value)
		return (-1);
	if(*value == '+' && *(value + 1) == '=')
		return 2;
	if(*value == '=')
		return 1;
	return -1;
}

char    *delete_plus(char *str)
{
    char    *value;
    char    *tmp;
    int        i;

    i = 0;
    tmp = str;
    if(*tmp == '+')
        value = malloc(ft_strlen(tmp));
    else
        value = malloc(ft_strlen(tmp) + 1);
	if (!value)
		return (NULL);
    if(*tmp == '+')
        tmp += 1;
    while(*tmp)
    {
        value[i] = *tmp;
        tmp++;
        i++;
    }
    value[i] = '\0';
	free(str);
    return (value);
}

char    *delete_eq(char *str)
{
    char    *value;
    char    *tmp;
    int        i;

    i = 0;
    tmp = str;
	value = malloc(ft_strlen(tmp));
	if (!value)
		return (NULL);
	tmp++;
    while(*tmp)
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
	t_env *tmp;

	tmp = (*env);
	while(tmp)
	{
		if(ft_strcmp(tmp->key, key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	add_value(char *key, char *value, t_env **env, int append)
{
	t_env	*tmp;
	char	*t = value;

	tmp = (*env);
	while(tmp)
	{
		if(ft_strcmp(tmp->key, key) == 0)
		{
			if(append == 1)
			{
				value = delete_eq(value);
				tmp->value = test(tmp->value, value);
				free(value);
			}
			else
			{
				if (!t)
					(tmp)->equal = 0;
				else if (t[0] == '=' && tmp->value != NULL)
				{
					t++;
					(tmp)->equal = 1;
				}
				free(tmp->value);
				tmp->value = ft_strdup(t);
				free(value);
			}
			return ;
		}
		tmp = tmp->next;
	}
}

void	send_to_stack_env(char *value, char *key, t_env **env)
{
	t_env	*node;

	node = NULL;
	if(check_value(value) == 1)
	{
		if(check_key_in_path(key, env) == 1)
			add_value(key, value, env, 0);
		else
		{
			node = ft_lstnew_env(key, value);
			ft_lstadd_back_env(env, node);
			free(value);
		}
	}
	else if(check_value(value) == 2)
	{
		value = delete_plus(value);
		if(check_key_in_path(key, env) == 1)
			add_value(key, value, env, 1);
		else
		{
			node = ft_lstnew_env(key, value);
			free(value);
			ft_lstadd_back_env(env, node);
		}
	}
	else
	{
		if(check_key_in_path(key, env) == 1)
		{
			free(value);
			return ;
		}
		node = ft_lstnew_env(key, value);
		free(value);
		ft_lstadd_back_env(env, node);
	}
}

int check_key_env(char *key)
{
	if((*key >= '0' && *key <= '9') || ft_strlen(key) == 0)
		return (1);
	while(*key)
	{
		if ((*key < 'a' || *key > 'z') && (*key < 'A' || *key > 'Z')
			&& (*key < '0' || *key > '9') && *key != '_')
			return (1);
		key++;
	}
	return (0);
}

void    ft_export(t_joins **head, t_env **env)
{
	char	*command;
	char	*key;
	char	*value;
	int		i;

	key = NULL;
	value = NULL;
	i = 1;

	if (!(*head)->content[i])
		print_sorted_env(env, head);
	else
	{
		while ((*head)->content[i])
		{
			if(ft_strcmp((*head)->content[i], "\"\"") == 0 || ft_strcmp((*head)->content[i], "\'\'") == 0)
			{
				ft_putstr("Minishell$ export: `': not a valid identifier\n", 2);
				// ft_lstclear_joins(head);
				i++;
				continue;
			}
			command = ft_strdup((*head)->content[i]);
			key = befor_equal(command);
			if (check_key_env(key) == 1)
			{
				printf("Minishell$ unset: `%s': not a valid identifier\n", command);
				free(command);
				free(key);
				// ft_lstclear_joins(head);
				i++;
				break ;
			}
			value = after_equal(command);
			send_to_stack_env(value, key, env);
			free(command);
			free(key);
			i++;
		}
	}
	// ft_exit_status(env, "0");
	// ft_lstclear_joins(head);
}
