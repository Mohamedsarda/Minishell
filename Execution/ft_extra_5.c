#include "../minishell.h"

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

void	ft_check_run_norm_2(char **environ, char *command,
	t_joins **head, char **tmp)
{
	int	j;

	j = -1;
	if (tmp == NULL || *tmp == NULL)
	{
		ft_putstr("Minishell$ ", 2);
		ft_putstr(command, 2);
		ft_putstr(": No such file or directory\n", 2);
		exit(127);
	}
	while (tmp[++j])
	{
		tmp[j] = test(tmp[j], "/");
		tmp[j] = test(tmp[j], (*head)->content[0]);
		if (access(tmp[j], X_OK) == 0)
			execve(tmp[j], (*head)->content, environ);
	}
	com_not_found(command);
}

int	check_nmbr(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}

void	ft_more_args(char	*str, t_env **env)
{
	if (check_nmbr(str))
	{
		ft_putstr("Minishell$: exit: numeric argument required\n", 2);
		ft_exit_status(env, "255");
		exit(255);
	}
	else
	{
		ft_putstr("Minishell$: exit: too many arguments\n", 2);
		ft_exit_status(env, "1");
		return ;
	}
}
