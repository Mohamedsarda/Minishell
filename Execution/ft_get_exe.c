#include "../minishell.h"

void	ft_run_commad(t_joins **head, t_env *env, char *type)
{
	if (ft_strcmp(type, "echo") == 0)
		ft_echo(head, env);
	else if (ft_strcmp(type, "pwd") == 0)
		ft_pwd(head);
	else if (ft_strcmp(type, "env") == 0)
		ft_env(env, head);
	else if (ft_strcmp(type, "cd") == 0)
		ft_cd(head);
	else if (ft_strcmp(type, "export") == 0)
		ft_export(head, env);
	else
		ft_run(head, env);
}
