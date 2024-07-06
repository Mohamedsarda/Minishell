#include "../minishell.h"

void	ft_unlink_free(char *str)
{
	unlink(str);
	signal(SIGINT, ft_sighandler);
	free(str);
}

int	run_pipes(t_joins	**stack_2, t_env **env)
{
	t_joins	*tmp;
	int		is;

	tmp = (*stack_2);
	is = 0;
	while (tmp)
	{
		is = 0;
		if (!tmp->content && tmp->out == 1 && tmp->in == 0)
			is = 1;
		tmp = tmp->next;
	}
	if (is)
		return (ft_lstclear_joins(stack_2), 1);
	ft_is_pipe(stack_2, env);
	return (0);
}

int	run_all_com(t_joins	**stack_2, t_env **env)
{
	t_joins	*tmp;

	tmp = (*stack_2);
	if (tmp && !tmp->next)
	{
		if (tmp->content != NULL)
			ft_run_commad(stack_2, env, tmp->content[0]);
	}
	else
		if (run_pipes(stack_2, env) == 1)
			return (1);
	return (0);
}
