#include "../minishell.h"

static void	ft_print_env(char *key, char *value, int fd)
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
		if ((env->value && env->equal && env->print))
			ft_print_env(env->key, env->value, fd);
		env = env->next;
	}
	if (fd != 1)
		close(fd);
	ft_exit_status(env_tmp, "0");
}
