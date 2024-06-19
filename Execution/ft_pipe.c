#include "../minishell.h"
#include <sys/stat.h>
int	ft_joinssize(t_joins *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

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

void	ft_run_2(t_joins **head, t_env **env)
{
	char	*command;

	command = ft_strdup((*head)->content[0]);
	char **environ = ft_create_env_from_stack(*env);
	check_run_2(environ, command, head, env);
	free_split(environ);
	free(command);
}

void	ft_run_commad_2(t_joins **head, t_env **env, char *type)
{
	if (ft_strcmp(type, "echo") == 0)
		ft_echo(head, env);
	else if (ft_strcmp(type, "pwd") == 0)
		ft_pwd(head, 0);
	else if (ft_strcmp(type, "env") == 0)
		ft_env(env, head);
	else if (ft_strcmp(type, "cd") == 0)
		ft_cd(head, env);
	else if (ft_strcmp(type, "export") == 0)
		ft_export(head, env);
	else if (ft_strcmp(type, "unset") == 0)
		ft_unset(head, env);
	else if (ft_strcmp(type, "exit") == 0)
		ft_exit(head, env, 1);
	else
		ft_run_2(head, env);
}

void	ft_dup(t_joins **head, int *fd, int *old)
{
	close(fd[0]);
	if ((*head)->in < 0 || (*head)->out < 0)
		exit (1);
	if ((*head)->out > 2)
		dup2((*head)->out, 1);
	else if ((*head)->next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if ((*head)->in > 2)
		dup2((*head)->in, 0);
	else if (*old != -1)
	{
		dup2(*old, 0);
		close(*old);
	}
}

void	ft_is_pipe(t_joins **head, t_env **env)
{
	int	pipes[2];
	int	pid;
	int	old;
	int	status;

	old = -1;
	while ((*head) && !(*head)->error)
	{
		pipe(pipes);
		pid = fork();
		if (pid == -1)
		{
			perror("Minishell$ ");
			close(pipes[1]);
			close(pipes[0]);
			break;
		}
		if (pid == 0)
		{
			ft_dup(head, pipes, &old);
			if ((*head)->content && !(*head)->content[0])
				exit(0);
			if ((*head)->content)
				ft_run_commad_2(head, env, (*head)->content[0]);
			close(pipes[1]);
			exit(0);
		}
		else if (pid > 0)
		{
			close(pipes[1]);
			if (old != -1)
				close(old);
			old = pipes[0];
			ft_next_node_joins(head);
		}
		else
		{
			perror("fork");
			exit(1);
		}
	}
	if (old > 0)
		close(old);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	int es = WEXITSTATUS(status);
	char *ppppp = ft_itoa(es);
	ft_exit_status(env, ppppp);
	free(ppppp);
}
