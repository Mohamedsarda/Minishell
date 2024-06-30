#include "../minishell.h"

char	*get_path(t_env **env)
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

void	ft_check_slash(char *command, t_env **env)
{
	int		i;
	char	*err;

	(void)env;
	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
		{
			err = ft_strjoin("Minishell$ : ", command);
			perror(err);
			free(err);
			exit(127);
		}
		i++;
	}
}

char	**ft_create_env_from_stack(t_env *env)
{
	char	**dst;
	int		size;
	int		i;

	size = ft_env_size(env);
	i = 0;
	dst = (char **)malloc(sizeof(char *) * (size + 1));
	if (!dst)
		return (NULL);
	while (i < size)
	{
		dst[i] = ft_strjoin(env->key, "=");
		dst[i] = test(dst[i], env->value);
		i++;
		env = env->next;
	}
	return (dst[i] = NULL, dst);
}

void	check_run(char **environ, char *command, t_joins **head, t_env **env)
{
	char		**tmp;
	pid_t		pid;
	int			status;
	char		*path;

	pid = fork();
	path = get_path(env);
	if (pid < 0)
	{
		perror("fork fail");
		exit(1);
	}
	if (pid == 0)
	{
		ft_check_run_norm_1(environ, command, head, env);
		tmp = ft_split(path, ':');
		ft_check_run_norm_2(environ, command, head, tmp);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		ft_check_sig_fork(status, env);
	else
		ft_change_status_fork(status, env);
	free(path);
}

void	ft_run(t_joins **head, t_env **env)
{
	char	*command;
	char	**environ;

	command = ft_strdup((*head)->content[0]);
	environ = ft_create_env_from_stack(*env);
	check_run(environ, command, head, env);
	free(command);
	free_split(environ);
}
