#include "../minishell.h"

void	ft_add_value_2(char *value, t_env *tmp, int append, char *t)
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
			ft_add_value_2(value, tmp, append, t);
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

void	ft_print_error_export(t_env **env, int is, char *command)
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

void	ft_export(t_joins **head, t_env **env)
{
	int		i;

	i = 1;
	ft_exit_status(env, "0");
	if (!(*head)->content[i])
		print_sorted_env(env, head);
	else
		ft_export_extra(head, env, &i);
}
