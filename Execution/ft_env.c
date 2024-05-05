#include "../minishell.h"

void	ft_env(t_env *env)
{
	while (env)
	{
		ft_putstr(env->key, 1);
		ft_putstr("=", 1);
		ft_putstr(env->value, 1);
		ft_putstr("\n", 1);
		env = env->next;
	}
}
