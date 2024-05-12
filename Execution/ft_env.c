#include "../minishell.h"

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
	while (env)
	{
		if (ft_strlen(env->value) > 0)
		{
			ft_putstr(env->key, fd);
			if (env->value[0] != '=')
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
