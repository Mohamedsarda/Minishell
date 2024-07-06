#include "../minishell.h"

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

static unsigned char	ft_atoi(char *str)
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

int	ft_atoi_checker(char *str)
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
	return (1);
}

void	ft_one_args(char	*str, t_env **env, unsigned int nbr, t_joins **head)
{
	char	*a;

	a = NULL;
	if (check_nmbr(str) == 1 || ft_atoi_checker(str) == 255 || ft_space(str))
	{
		ft_putstr("Minishell$: exit: numeric argument required\n", 2);
		ft_exit_status(env, "255");
		exit(255);
	}
	else
	{
		nbr = ft_atoi(str);
		ft_lstclear_joins(head);
		ft_lstclear_env(env);
		a = ft_itoa(nbr);
		ft_exit_status(env, a);
		free(a);
		exit(nbr);
	}
}

void	ft_exit(t_joins **head, t_env **env, int fd)
{
	t_env			*tmp;
	unsigned int	nbr;
	int				i;

	i = 1;
	nbr = 0;
	tmp = ft_get_status_pos(*env, "?");
	while ((*head)->content[i])
		i++;
	if (fd == 2)
		ft_putstr("exit\n", fd);
	if (i == 1)
		exit(ft_atoi4(tmp->value));
	if (i != 2)
	{
		ft_more_args((*head)->content[1], env);
		return ;
	}
	else
		ft_one_args((*head)->content[1], env, nbr, head);
	exit(nbr);
}
