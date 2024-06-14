#include "../minishell.h"

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

void	add_value(char *key, char *value, t_env **env, int append)
{
	t_env	*tmp;
	char	*t;

	tmp = (*env);
	t = value;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (append == 1)
			{
				value = delete_eq(value);
				tmp->print = 1;
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
				tmp->print = 1;
				free(value);
			}
			return ;
		}
		tmp = tmp->next;
	}
}

void	send_to_stack_env(t_joins **head, char *value, char *key, t_env **env)
{
	t_env	*node;

	node = NULL;
	if (check_value(value) == 1)
	{
		if (check_key_in_path(key, env) == 1)
			add_value(key, value, env, 0);
		else
		{
			node = ft_lstnew_env(key, value);
			ft_lstadd_back_env(env, node);
			free(value);
		}
	}
	else if (check_value(value) == 2)
	{
		value = delete_plus(value);
		if (check_key_in_path(key, env) == 1)
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
		if (check_key_in_path(key, env) == 1)
		{
			free(value);
			return ;
		}
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

void	ft_export(t_joins **head, t_env **env)
{
	char	*command;
	char	*key;
	char	*value;
	int		i;

	key = NULL;
	value = NULL;
	i = 1;
	ft_exit_status(env, "0");
	if (!(*head)->content[i])
		print_sorted_env(env, head);
	else
	{
		while ((*head)->content[i])
		{
			if (ft_strcmp((*head)->content[i], "\"\"") == 0
				|| ft_strcmp((*head)->content[i], "\'\'") == 0)
			{
				ft_putstr("Minishell$ export: `': not a valid identifier\n", 2);
				ft_exit_status(env, "1");
				i++;
				continue ;
			}
			command = ft_strdup((*head)->content[i]);
			key = befor_equal(command);
			if (check_key_env(key) == 1)
			{
				ft_exit_status(env, "1");
				ft_putstr("Minishell$ export: `", 2);
				ft_putstr(command, 2);
				ft_putstr("': not a valid identifier\n", 2);
			}
			else
			{
				value = after_equal(command);
				send_to_stack_env(head, value, key, env);
			}
			free(command);
			free(key);
			i++;
		}
	}
}
