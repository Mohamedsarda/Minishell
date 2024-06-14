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
// start
void	ft_check_slash(char *command, t_env **env)
{
	int	i;
	char	*err;
	(void)env;
	i = 0;
	while(command[i])
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
void	com_not_found(char *command)
{
	ft_putstr("Minishell$ ", 2);
	ft_putstr(command, 2);
	ft_putstr(": command not found\n", 2);
	exit(127);
}
char	**ft_create_env_from_stack(t_env *env)
{
	char	**dst;
	int		size;
	// char	*tmp;
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
	int			j;
	pid_t		p;
	int			status;
	char		*path;

	j = -1;
	p = fork();
	path = get_path(env);
	if (p < 0)
	{
		perror("fork fail");
		exit(1);
	}
	if (p == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if ((*head)->out != 1)
			dup2((*head)->out, 1);
		if ((*head)->in != 0)
			dup2((*head)->in, 0);
		execve(command, (*head)->content, environ);
		ft_check_slash(command, env);
		tmp = ft_split(path, ':');
		if (tmp == NULL || *tmp == NULL)
		{
			perror("Minishell$ ");
			exit(127) ;
		}
		while (tmp[++j])
		{
			tmp[j] = test(tmp[j], "/");
			tmp[j] = test(tmp[j], (*head)->content[0]);
			if (access(tmp[j], X_OK) == 0)
				execve(tmp[j], (*head)->content, environ);
		}
		com_not_found(command);
	}
	else
	{
		waitpid(p, &status, 0);
		while (wait(NULL) != -1)
		;
		// if (waitpid(p, &status, 0) == 0)
		// {
		// 	perror("waitpid() failed");
		// 	ft_exit_status(env, "1");
		// 	exit(EXIT_FAILURE);
		// }

		int es = WEXITSTATUS(status);
		char *ppppp = ft_itoa(es);
		ft_exit_status(env, ppppp);
		free(ppppp);
	}
	free(path);
}

void	ft_run(t_joins **head, t_env **env)
{
	char	*command;

	command = ft_strdup((*head)->content[0]);
	char **environ = ft_create_env_from_stack(*env);
	check_run(environ, command, head, env);
	free(command);
	free_split(environ);
	// ft_next_node_joins(head);
}
