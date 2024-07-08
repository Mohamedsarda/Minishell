/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_func_part9.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:40:42 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:40:43 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	com_not_found(char *command)
{
	ft_putstr("Minishell$ ", 2);
	ft_putstr(command, 2);
	ft_putstr(": command not found\n", 2);
	exit(127);
}

void	ft_check_sig_fork(int status, t_env **env)
{
	if (status == 3)
	{
		ft_putstr("Quit: 3\n", 2);
		ft_exit_status(env, "131");
	}
	else
	{
		ft_putstr("\n", 2);
		ft_exit_status(env, "130");
	}
}

void	ft_change_status_fork(int status, t_env **env)
{
	char	*final_status;

	final_status = ft_itoa(WEXITSTATUS(status));
	ft_exit_status(env, final_status);
	free(final_status);
}

void	ft_check_slash(char *command, t_env **env)
{
	int		i;
	char	*err;

	(void)env;
	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
		{
			err = ft_strjoin("Minishell$ : ", command);
			perror(err);
			free(err);
			exit(127);
		}
		i++;
	}
}

void	ft_check_run_norm_1(char **environ, char *command,
	t_joins **head, t_env **env)
{
	signal(SIGQUIT, SIG_DFL);
	if ((*head)->out != 1)
		dup2((*head)->out, 1);
	if ((*head)->in != 0)
		dup2((*head)->in, 0);
	execve(command, (*head)->content, environ);
	ft_check_slash(command, env);
}
