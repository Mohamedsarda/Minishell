#include "../minishell.h"

void	ft_run_2(t_joins **head, t_env **env)
{
	char	*command;
	char	**environ;

	command = ft_strdup((*head)->content[0]);
	environ = ft_create_env_from_stack(*env);
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

int	ft_handle_proc(t_joins **head, t_env **env, int pid, int *pipes, int *old)
{
	if (pid == -1)
	{
		perror("Minishell$ ");
		return (close(pipes[1]), close(pipes[0]), 0);
	}
	if (pid == 0)
	{
		ft_dup(head, pipes, old);
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
		if ((*old) != -1)
			close((*old));
		(*old) = pipes[0];
		ft_next_node_joins(head);
	}
	return (1);
}

void	ft_is_pipe(t_joins **head, t_env **env)
{
	int		pipes[2];
	int		pid;
	int		old;
	int		status;
	char	*final_status;

	old = -1;
	while ((*head) && !(*head)->error)
	{
		pipe(pipes);
		pid = fork();
		if (!ft_handle_proc(head, env, pid, pipes, &old))
			break ;
	}
	if (old > 0)
		close(old);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	final_status = ft_itoa(WEXITSTATUS(status));
	ft_exit_status(env, final_status);
	free(final_status);
}
