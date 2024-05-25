#include "../minishell.h"

void	ft_run_commad(t_joins **head, t_env **env, char *type)
{
	if (ft_strcmp(type, "echo") == 0)
		ft_echo(head);
	else if (ft_strcmp(type, "pwd") == 0)
		ft_pwd(head);
	else if (ft_strcmp(type, "env") == 0)
		ft_env(env, head);
	else if (ft_strcmp(type, "cd") == 0)
		ft_cd(head, env);
	else if (ft_strcmp(type, "export") == 0)
		ft_export(head, env);
	else if (ft_strcmp(type, "unset") == 0)
		ft_unset(head, env);
	else if (ft_strcmp(type, "exit") == 0)
		ft_exit(head, env);
	else if (!(*head)->next)
		ft_run(head, env);
	// else
	// 	ft_is_pipe(head);
	// t_joins *tmp = *head;
	// while (tmp)
	// {
	// 	int i = 0;
	// 	while (tmp->content[i])
	// 		printf("[%s]\n", tmp->content[i++]);
	// 	printf("out : [%d] | in : [%d]\n", tmp->out, tmp->in);
	// 	tmp = tmp->next;
	// }
}
