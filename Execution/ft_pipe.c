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
		ft_exit(head, env, 1);
	else
		ft_run_2(head, env);
	free(str);
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
	int		pipes[2];
	int		pid;
	int		old;
	int		status;

	old = -1;
	while ((*head) && !(*head)->error)
	{
		((pipe(pipes), pid = fork()));
		if (pid == -1)
			ft_fork_fail(pipes);
		if (pid == 0)
			ft_handle_proc_child(head, pipes, &old, env);
		else if (pid > 0)
			ft_handle_proc_parent(head, pipes, &old);
	}
	if (old > 0)
		close(old);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	if (WIFSIGNALED(status))
		ft_check_sig_fork(status, env);
	else
		ft_change_status_fork(status, env);
}
