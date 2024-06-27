#include "../minishell.h"

char	*get_path_2(t_env **env)
{
	char	*path;
	t_env	*env_tmp;

	path = NULL;
	env_tmp = (*env);
	while (env_tmp)
	{
		if (ft_strcmp(env_tmp->key, "PATH") == 0)
		{
			if (!env_tmp->value[0] || !env_tmp->value)
				path = ft_strdup(NULL);
			else
				path = ft_strdup(env_tmp->value);
			break ;
		}
		env_tmp = env_tmp->next;
	}
	return (path);
}

void	check_run_2(char **environ, char *command, t_joins **head, t_env **env)
{
	char		**tmp;
	int			j;
	char		*path;

	j = -1;
	path = get_path_2(env);
	signal(SIGQUIT, SIG_DFL);
	execve(command, (*head)->content, environ);
	ft_check_slash(command, env);
	tmp = ft_split(path, ':');
	if (tmp == NULL || *tmp == NULL)
	{
		ft_exit_status(env, "1");
		perror("Minishell$ ");
		exit(1);
	}
	while (tmp[++j])
	{
		tmp[j] = test(tmp[j], "/");
		tmp[j] = test(tmp[j], (*head)->content[0]);
		if (access(tmp[j], X_OK) == 0)
			execve(tmp[j], (*head)->content, environ);
	}
	com_not_found(command);
	free(path);
}
