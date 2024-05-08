#include "../minishell.h"

void    run_com(char *com, t_joins **head)
{
		pid_t p = fork();
		if(p<0)
		{
			perror("fork fail");
			exit(1);
		}
		if (p == 0)
		{
			if ((*head)->out != 1)
				close(1);
			dup2((*head)->out, STDOUT_FILENO);
			execve(com, (*head)->content, NULL);
		}
		else
			wait(NULL);
}

char    *get_path(t_env *env)
{
	char *PATH;
	
	PATH = NULL;
	while(env)
	{
		if(ft_strcmp(env->key, "PATH") == 0)
		{
			if (!env->value[0] || !env->value)
				PATH = ft_strdup(NULL);
			else
				PATH = ft_strdup(env->value);
			break;
		}
		env = env->next;
	}
	return (PATH);
}

void    ft_run(t_joins **head, t_env *env)
{
	char    *command;
	char    *PATH;
	int		j;
	int		i;
	char    **tmp;

	j = -1;
	i = 0;
	command = ft_strdup((*head)->content[0]);
	PATH = get_path(env);
	tmp = ft_split(PATH, ':');
	if (tmp == NULL || *tmp == NULL)
	{
		ft_putstr("command not found\n", 2);
		return ;
	}
	while (tmp[++j])
	{
		tmp[j] = test(tmp[j], "/");
		tmp[j] = test(tmp[j], command);
		if(access(tmp[j], X_OK) == 0)
		{
				i++;
			run_com(tmp[j], head);
			break;
		}
	}
	if(i == 0)
		ft_putstr("command not found\n", 2);
	free_split(tmp);
	free(PATH);
	free(command); 
	ft_lstclear_joins(head);
}