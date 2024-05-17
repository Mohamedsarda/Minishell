#include "../minishell.h"

void	ft_exit(t_joins **head, t_env **env)
{
	ft_lstclear_env(env);
	ft_lstclear_joins(head);
	exit(0);
}

t_env	*ft_get_status_pos(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "?") == 0)
			return env;
		env = env->next;
	}
	return env;
}

void	ft_exit_status(t_env **env, char *status)
{
	t_env	*tmp;

	tmp = (*env);
	tmp = ft_get_status_pos(tmp);
	free(tmp->value);
	tmp->value = NULL;
	tmp->value = ft_strdup(status);
	// printf("%s:%s\n", tmp->key, tmp->value);
	// puts("++++++");
}
