#include "../minishell.h"

void	ft_run_commad(t_joins **head, t_env **env, char *type)
{
	if(type == NULL)
		return ;
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
		ft_exit(head, env, 2);
	else if (!(*head)->next)
		ft_run(head, env);
	ft_next_node_joins(head);
}
