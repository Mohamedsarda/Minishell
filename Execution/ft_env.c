#include "../minishell.h"

void	ft_env(t_env *env, t_joins **stack_2)
{
	t_joins	*tmp;
	int		fd;

	tmp = (*stack_2);
	if (tmp->out != 0 && tmp->in >= 0)
		fd = tmp->out;
	else
		fd = tmp->in;
	while (env)
	{
		ft_putstr(env->key, fd);
		ft_putstr("=", fd);
		ft_putstr(env->value, fd);
		ft_putstr("\n", fd);
		env = env->next;
	}
	printf("%d\n", fd);
	close(fd);
	ft_lstclear_joins(stack_2);
}
