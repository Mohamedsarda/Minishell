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
	while(*str  && *str != '=')
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
	while(*str && *str != '=')
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
	while(*str && *str != '=')
		str++;
	if (*str)
		str++;
	while (*str && *str)
	{
		key[i] = *str;
		str++;
		i++;
	}
	key[i] = '\0';
	return (key);
}

void	ft_get_env_size(char *key, int *size)
{
	if (key[0])
		(*size) += key[0];
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
    int		i;
    int		j;

	count = ft_env_size(head);
    t_env **arr = malloc(count * sizeof(t_env *));
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
        printf("%s=%s\n", arr[i]->key, arr[i]->value);
	// ft_lstclear_env(arr);
}

void    ft_export(t_joins **head, t_env *env)
{
	char	*command;
	char	*key;
	char	*value;
	t_env *node = env;
	int		i;
	int		j;

	i = 1;
	j = 0;
	while((*head)->content[i])
	{
		command = ft_strdup((*head)->content[i]);
		key = befor_equal(command);
		while(key[j])
		{
			if(check_key(key[j]))
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
		node = ft_lstnew_env(key, value);
		ft_lstadd_back_env(&env, node);
		i++;
	}
	if ((*head)->content[i])
	{
		free(command);
		free(key);
		free(value);
	}
	else
	{
		t_env *tmp = env;
		while (tmp)
		{
			ft_get_env_size(tmp->key, &tmp->size);
			tmp = tmp->next;
		}
		print_sorted_env(env);
	}
	ft_lstclear_joins(head);
}