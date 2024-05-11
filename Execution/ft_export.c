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

void	print_sorted_env(t_env *head)
{
	int		count;
	t_env	*current;
	t_env	**arr;
	int		i;
	int		j;

	count = ft_env_size(head);
	arr = (t_env **)malloc(count * sizeof(t_env *));
	if (!arr)
		return ;
	current = head;
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
		printf("declare -x %s=%s\n", arr[i]->key, arr[i]->value);
	free(arr);
}

int	check_value(char *value)
{
	if(*value == '+' && *(value + 1) == '=')
		return 1;
	if(*value == '=')
		return 2;
	return -1;
}

char	*delete_eq(char *str)
{
	char	*value;
	char	*tmp;
	int		i;

	i = 0;
	tmp = str;
	if(*str == '+')
		value = malloc(ft_strlen(str) - 1);
	else
		value = malloc(ft_strlen(str));
	if(*str == '+')
		str += 2;
	else
		str++;
	while(*str)
	{
		value[i] = *str;
		str++;
		i++;
	}
	return (value);
}

int	check_key_in_path(char *key, t_env *env)
{
	while(env)
	{
		if(ft_strcmp(env->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}
void	add_value(char *key, char *value, t_env **env, int is)
{
	while((*env))
	{
		if(ft_strcmp((*env)->key, key) == 0)
		{
			if(is == 1)
			{
				(*env)->value = test((*env)->value, value);
				free(value);
			}
			else
			{
				free((*env)->value);
				(*env)->value = NULL;
				(*env)->value = value;
			}
		}
		(*env) = (*env)->next;
	}
}
void	send_to_stack_env(char *value, char *key, t_env *env)
{
	t_env	*node;

	node = env;
	if(check_value(value) == 2)
	{
		value = delete_eq(value);
		if(check_key_in_path(key, env) == 1)
			add_value(key, value, &env, 0);
		else
		{
			node = ft_lstnew_env(key, value);
			ft_lstadd_back_env(&env, node);
			free(value);
		}
	}
	else if(check_value(value) == 1)
	{
		value = delete_eq(value);
		if(check_key_in_path(key, env) == 1)
			add_value(key, value, &env, 1);
		else
		{
			node = ft_lstnew_env(key, value);
			ft_lstadd_back_env(&env, node);
			free(value);
		}
	}
	else
	{
		node = ft_lstnew_env(key, value);
		ft_lstadd_back_env(&env, node);
	}
}

void    ft_export(t_joins **head, t_env *env)
{
	char	*command;
	char	*key;
	char	*value;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (!(*head)->content[i])
		print_sorted_env(env);
	else
	{
		while ((*head)->content[i])
		{
			command = ft_strdup((*head)->content[i]);
			key = befor_equal(command);
			while (key[j])
			{
				if (check_key(key[j]))
				{
					ft_putstr("syntax error near unexpected token\n", 2);
					free(command);
					free(key);
					ft_lstclear_joins(head);
					return ;
				}
				j++;
			}
			value = after_equal(command);
			send_to_stack_env(value, key, env);
			
			i++;
		}
		free(command);
		free(key);
		free(value);
	}
	ft_lstclear_joins(head);
}
