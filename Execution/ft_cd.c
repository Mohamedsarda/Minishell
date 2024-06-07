#include "../minishell.h"

char	*ft_get_val_env(t_joins **head, t_env **env, char *key)
{
	t_env	*env_head;

	env_head = (*env);
	(void)head;
	while (env_head)
	{
		if (ft_strcmp(env_head->key, key) == 0)
			return (env_head->value);
		env_head = env_head->next;
	}
	return (NULL);
}

void	ft_change_pwd(t_joins **head, t_env **env)
{
	t_env	*oldpwd;
	t_env	*pwd;

	pwd = ft_get_status_pos(*env, "PWD");
	oldpwd = ft_get_status_pos(*env, "OLDPWD");
	free(oldpwd->value);
	oldpwd->value = ft_strdup(pwd->value);
	free(pwd->value);
	pwd->value = ft_pwd(head, 1);
}

void	ft_cd(t_joins **head, t_env **env)
{
	char	*tmp;
	char	*home;

	tmp = NULL;
	home = ft_get_val_env(head, env, "HOME");
	if (!home && !(*head)->content[1])
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
	ft_change_pwd(head, env);
}

	// if (access(pwd->value, F_OK) == -1)
	// {
	// 	ft_exit_status(env, "1");
	// 	perror("Minishell$ ");
	// }
	// ft_lstclear_joins(head);
