/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:39:27 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:39:28 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_run_2(t_joins **head, t_env **env)
{
	char	*command;
	char	**environ;

	command = ft_strdup((*head)->content[0]);
	environ = ft_create_env_from_stack(*env);
	check_run_2(environ, command, head, env);
	free_split(environ);
	free(command);
}

static void	ft_run_commad_2(t_joins **head, t_env **env, char *type)
{
	char	*str;

	if (type == NULL)
		return ;
	str = ft_to_lower(type);
	if (ft_strcmp(str, "echo") == 0)
		ft_echo(head, env);
	else if (ft_strcmp(str, "pwd") == 0)
		ft_pwd(head, 0);
	else if (ft_strcmp(str, "env") == 0)
		ft_env(env, head);
	else if (ft_strcmp(str, "cd") == 0)
		ft_cd(head, env);
	else if (ft_strcmp(str, "export") == 0)
		ft_export(head, env);
	else if (ft_strcmp(str, "unset") == 0)
		ft_unset(head, env);
	else if (ft_strcmp(str, "exit") == 0)
		ft_exit(head, env, 1);
	else
		ft_run_2(head, env);
	free(str);
}

static void	ft_dup(t_joins **head, int *fd, int *old)
{
	close(fd[0]);
	if ((*head)->in < 0 || (*head)->out < 0)
		exit (1);
	if ((*head)->out > 2)
		dup2((*head)->out, 1);
	else if ((*head)->next)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if ((*head)->in > 2)
		dup2((*head)->in, 0);
	else if (*old != -1)
	{
		dup2(*old, 0);
		close(*old);
	}
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
