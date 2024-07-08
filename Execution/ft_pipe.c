/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:40:06 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:52:23 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_path_2(t_env **env)
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
		perror("Minishell$ ");
		exit(127);
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

static void	ft_fork_fail(int *pipes)
{
	perror("Minishell$ ");
	close(pipes[1]);
	close(pipes[0]);
	exit (1);
}

static void	ft_handle_proc_parent(t_joins **head, int *pipes, int *old)
{
	close(pipes[1]);
	if ((*old) != -1)
		close((*old));
	(*old) = pipes[0];
	ft_next_node_joins(head);
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
