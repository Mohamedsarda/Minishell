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
int	check_is_fath(char *str)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
void	check_run(char *PATH, char *command, t_joins **head, t_env **env)
{
	char		**tmp;
	int			j;
	int			i;
	pid_t		p;
	extern char	**environ;

	j = -1;
	i = 0;
	p = fork();
	if (p < 0)
	{
		ft_exit_status(env, "1");
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
		tmp = ft_split(PATH, ':');
		if (tmp == NULL || *tmp == NULL)
		{
			ft_exit_status(env, "1");
			perror("Minishell$ ");
			exit(1) ;
		}
		while (tmp[++j])
		{
			tmp[j] = test(tmp[j], "/");
			tmp[j] = test(tmp[j], command);
			if (access(tmp[j], X_OK) == 0)
				execve(tmp[j], (*head)->content, environ);
		}
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
		ft_putstr("Minishell$ ", 2);
		ft_putstr(command, 2);
		ft_putstr(": command not found\n", 2);
		exit(1);
	}
	else
		wait(NULL);
}

void	ft_run(t_joins **head, t_env **env)
{
	char	*command;
	char	*path;
	int		j;
	int		i;

	j = -1;
	i = 0;
	command = ft_strdup((*head)->content[0]);
	path = get_path(env);
	check_run(path, command, head, env);
	free(path);
	free(command);
	// ft_next_node_joins(head);
}
