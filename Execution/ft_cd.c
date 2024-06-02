#include "../minishell.h"

char	*ft_get_val_env(char *tmp, t_env **env, char *key, int is)
{
	t_env	*env_head;
	char	buffer[1024];

	env_head = (*env);
	(void)is;
	(void)tmp;
	while (env_head)
	{
		if (ft_strcmp(env_head->key, key) == 0)
			return (env_head->value);
		env_head = env_head->next;
	}
	if (is == 1)
	{

		getcwd(buffer, sizeof(buffer));
		free(env_head->value);
		env_head->value = NULL;
		env_head->value = ft_strdup(buffer);
	}
	return (NULL);
}

void	ft_cd(t_joins **head, t_env **env)
{
	char	*tmp = NULL;
	char	*home;
	char	*pwd;

	home = ft_get_val_env(tmp, env, "HOME", 0);
	if (!home)
	{
		ft_putstr("Minishell$ cd: HOME not set\n", 2);
		return ;
	}
	ft_exit_status(env, "0");
	tmp = (*head)->content[1];
	if (!tmp)
		tmp = home;
	if (chdir(tmp) != 0)
	{
		ft_exit_status(env, "1");
		perror("Minishell$ ");
	}
	pwd = ft_get_val_env(tmp, env, "PWD", 1);
	if (access(pwd, F_OK) == -1)
	{
		pwd = ft_get_val_env(tmp, env, "PWD", 2);
		ft_exit_status(env, "1");
		perror("Minishell$ ");
	}
	// ft_lstclear_joins(head);
}
