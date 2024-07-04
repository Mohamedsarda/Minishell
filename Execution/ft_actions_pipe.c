#include "../minishell.h"

void	ft_fork_fail(int *pipes)
{
	perror("Minishell$ ");
	close(pipes[1]);
	close(pipes[0]);
	exit (1);
}

void	ft_handle_proc_parent(t_joins **head, int *pipes, int *old)
{
	close(pipes[1]);
	if ((*old) != -1)
		close((*old));
	(*old) = pipes[0];
	ft_next_node_joins(head);
}

void	ft_handle_proc_child(t_joins **head, int *pipes,
	int *old, t_env **env)
{
	ft_dup(head, pipes, old);
	if ((*head)->content && !(*head)->content[0])
		exit(0);
	if ((*head)->content)
		ft_run_commad_2(head, env, (*head)->content[0]);
	close(pipes[1]);
	exit(0);
}
