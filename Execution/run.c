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
			printf("out : %d\n",(*head)->out);
			printf("in : %d\n",(*head)->in);
			if ((*head)->out != 1)
				close(1);
			if ((*head)->in != 0)
				dup2((*head)->in, STDIN_FILENO);
			else
				dup2((*head)->out, STDIN_FILENO);
			execve(com, (*head)->content, NULL);
		}
		// else
			wait(NULL);
}

char    *get_path(t_env **env)
{
	char	*PATH;
	t_env	*env_tmp;
	
	PATH = NULL;
	env_tmp = (*env);
	while (env_tmp)
	{
		if(ft_strcmp(env_tmp->key, "PATH") == 0)
		{
			if (!env_tmp->value[0] || !env_tmp->value)
				PATH = ft_strdup(NULL);
			else
				PATH = ft_strdup(env_tmp->value);
			break;
		}
		env_tmp = env_tmp->next;
	}
	return (PATH);
}

void    ft_run(t_joins **head, t_env **env)
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