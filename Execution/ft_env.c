#include "../minishell.h"
void	env_equal(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while(tmp)
	{
		printf("[%s] || [%s] || [%d]\n", tmp->key, tmp->value, tmp->equal);
		if(!(tmp)->value)
			(tmp)->equal = 0;
		else if ((tmp)->value[0] == '=' && tmp->equal != 1)
		{
			(tmp)->value++;
			(tmp)->equal = 1;
		}
		tmp = tmp->next;
	}
}

void	ft_env(t_env **env_tmp, t_joins **stack_2)
{
	t_joins	*tmp;
	t_env	*env;
	int		fd;
	
	env = (*env_tmp);
	tmp = (*stack_2);
	if (tmp->out != 0 && tmp->in >= 0)
		fd = tmp->out;
	else
		fd = tmp->in;
	env_equal(env_tmp);
	while (env)
	{
		if (env->value && env->equal)
		{
			ft_putstr(env->key, fd);
			ft_putstr("=", fd);
			ft_putstr(env->value, fd);
			ft_putstr("\n", fd);
		}
		env = env->next;
	}
	if (fd != 1)
		close(fd);
	ft_next_node_joins(stack_2);
}

