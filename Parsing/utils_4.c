		#include "../minishell.h"

void	ft_print_export(t_env **arr, int count, int fd)
{
	int	i;

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
}

void	ft_swap_while(t_env **arr, int count)
{
	int	i;
	int	j;

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
}

void	print_sorted_env(t_env **head, t_joins **stack_2)
{
	int		count;
	t_env	*current;
	t_env	**arr;
	int		i;
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
	ft_swap_while(arr, count);
	ft_print_export(arr, count, fd);
	free(arr);
}

void	ft_exit_status(t_env **env, char *status)
{
	t_env	*tmp;

	tmp = (*env);
	tmp = ft_get_status_pos(tmp, "?");
	if (!tmp)
		return ;
	free(tmp->value);
	tmp->value = NULL;
	tmp->value = ft_strdup(status);
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
