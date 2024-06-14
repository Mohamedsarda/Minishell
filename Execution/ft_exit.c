#include "../minishell.h"
#include <limits.h>

int	ft_sign(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign *= -1;
		(*str)++;
	}
	return (sign);
}

unsigned char	ft_atoi(char *str)
{
	size_t	nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	while (*str && *str == ' ')
		str++;
	sign = ft_sign(&str);
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		if (nbr > LONG_MAX && !(nbr == ((size_t)LONG_MAX + 1) && sign == -1))
			return (255);
		str++;
	}
	while (*str && *str == ' ')
		str++;
	if (*str != '\0')
		return (255);
	return (nbr * sign);
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

void	ft_exit(t_joins **head, t_env **env, int fd)
{
	t_env			*tmp;
	unsigned int	nbr;
	char			*a;
	int				i;

	i = 1;
	nbr = 0;
	a = NULL;
	tmp = ft_get_status_pos(*env, "?");
	while ((*head)->content[i])
		i++;
	if (fd == 2)
		ft_putstr("exit\n", fd);
	if (i == 1)
		exit(ft_atoi4(tmp->value));
	if (i != 2)
	{
		if (check_nmbr((*head)->content[1]))
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
	else
	{
		if (check_nmbr((*head)->content[1]) == 255)
		{
			ft_putstr("Minishell$: exit: numeric argument required\n", 2);
			ft_exit_status(env, "255");
		}
		else
		{
			nbr = ft_atoi((*head)->content[1]);
			ft_lstclear_joins(head);
			ft_lstclear_env(env);
			a = ft_itoa(nbr);
			ft_exit_status(env, a);
			free(a);
		}
	}
	exit(nbr);
}

void	ft_exit_status(t_env **env, char *status)
{
	t_env	*tmp;

	tmp = (*env);
	tmp = ft_get_status_pos(tmp, "?");
	if (!tmp)
		return ;
	free(tmp->value);
	tmp->value = NULL;
	tmp->value = ft_strdup(status);
}
