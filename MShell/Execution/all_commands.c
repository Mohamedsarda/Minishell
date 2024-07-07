#include "../minishell.h"

char	*ft_to_lower(char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			res[i] = str[i] + 32;
		else
			res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	ft_run_commad(t_joins **head, t_env **env, char *type)
{
	char	*str;

	if (type == NULL)
		return ;
	str = ft_to_lower(type);
	if (ft_strcmp(str, "echo") == 0)
		ft_echo(head, env);
	else if (ft_strcmp(str, "pwd") == 0)
		ft_pwd(head, 0);
	else if (ft_strcmp(str, "env") == 0)
		ft_env(env, head);
	else if (ft_strcmp(str, "cd") == 0)
		ft_cd(head, env);
	else if (ft_strcmp(str, "export") == 0)
		ft_export(head, env);
	else if (ft_strcmp(str, "unset") == 0)
		ft_unset(head, env);
	else if (ft_strcmp(str, "exit") == 0)
		ft_exit(head, env, 2);
	else if (!(*head)->next)
		ft_run(head, env);
	free(str);
	ft_next_node_joins(head);
}

int	ft_env_size_hide(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (!(env->print == 1 && env->equal == 1))
			i++;
		env = env->next;
	}
	return (i);
}
