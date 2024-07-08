/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:39:30 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:39:32 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_get_val_env(t_joins **head, t_env **env, char *key)
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

static void	ft_create_newoldpwd(t_joins **head, t_env *pwd,
	t_env *oldpwd, t_env **env)
{
	char	*newpwd;

	newpwd = ft_pwd(head, 1);
	if (!pwd)
	{
		pwd = ft_lstnew_env("PWD", newpwd);
		pwd->print = 0;
		ft_lstadd_back_env(env, pwd);
		if (oldpwd)
		{
			free(oldpwd->value);
			oldpwd->value = ft_strdup("");
			oldpwd->equal = 1;
		}
	}
	if (!oldpwd)
	{
		oldpwd = ft_lstnew_env("OLDPWD", newpwd);
		oldpwd->print = 0;
		ft_lstadd_back_env(env, oldpwd);
	}
	free(newpwd);
}

static void	ft_change_pwd(t_joins **head, t_env **env)
{
	t_env	*oldpwd;
	t_env	*pwd;

	pwd = ft_get_status_pos(*env, "PWD");
	oldpwd = ft_get_status_pos(*env, "OLDPWD");
	if ((pwd && oldpwd))
	{
		free(oldpwd->value);
		oldpwd->value = ft_strdup(pwd->value);
		oldpwd->equal = 1;
		free(pwd->value);
		pwd->value = ft_pwd(head, 1);
	}
	else
		ft_create_newoldpwd(head, pwd, oldpwd, env);
}

void	ft_cd(t_joins **head, t_env **env)
{
	char	*tmp;
	char	*home;
	char	*check;

	tmp = NULL;
	home = ft_get_val_env(head, env, "HOME");
	ft_exit_status(env, "0");
	if (!home && !(*head)->content[1])
	{
		ft_putstr("Minishell$ cd: HOME not set\n", 2);
		ft_exit_status(env, "1");
		return ;
	}
	tmp = (*head)->content[1];
	if (!tmp || !tmp[0])
		tmp = home;
	((1) && (check = test(ft_pwd(head, 1), "/"), check = test(check, tmp)));
	if (chdir(tmp) != 0 || (access(check, F_OK) != 0))
	{
		ft_exit_status(env, "1");
		perror("Minishell$ ");
	}
	else
		ft_change_pwd(head, env);
	free(check);
}
