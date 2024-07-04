#include "../minishell.h"

void	env_equal(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!(tmp)->value)
			(tmp)->equal = 0;
		else if ((tmp)->value[0] == '=' && tmp->equal != 1)
		{
			(tmp)->value++;
			(tmp)->equal = 1;
		}
		tmp = tmp->next;
	}
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

void	ft_print_env(char *key, char *value, int fd)
{
	ft_putstr(key, fd);
	ft_putstr("=", fd);
	ft_putstr(value, fd);
	ft_putstr("\n", fd);
}

void	ft_env(t_env **env_tmp, t_joins **stack_2)
{
	t_joins	*tmp;
	t_env	*env;
	int		fd;

	env = (*env_tmp);
	if (ft_env_size(env) == 1)
	{
		ft_exit_status(env_tmp, "127");
		ft_putstr("Minishell$ env: No such file or directory\n", 2);
		return ;
	}
	tmp = (*stack_2);
	if (tmp->out != 0 && tmp->in >= 0)
		fd = tmp->out;
	else
		fd = tmp->in;
	while (env)
	{
		if (env->value && env->equal && env->print)
			ft_print_env(env->key, env->value, fd);
		env = env->next;
	}
	if (fd != 1)
		close(fd);
	ft_exit_status(env_tmp, "0");
}
