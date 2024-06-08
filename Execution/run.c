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
	
	i = 0;
	while(command[i])
		{
			if (command[i] == '/')
			{
				ft_exit_status(env, "127");
				printf("Minishell$ %s : No such file or directory\n", command);
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
void	check_run(char *PATH, char *command, t_joins **head, t_env **env)
{
	char		**tmp;
	int			j;
	pid_t		p;
	extern char	**environ;

	j = -1;
	p = fork();
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
		tmp = ft_split(PATH, ':');
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
		wait(NULL);
}

void	ft_run(t_joins **head, t_env **env)
{
	char	*command;
	char	*path;

	command = ft_strdup((*head)->content[0]);
	path = get_path(env);
	check_run(path, command, head, env);
	free(path);
	free(command);
	// ft_next_node_joins(head);
}
