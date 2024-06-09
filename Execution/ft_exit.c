#include "../minishell.h"

int ft_sign(char **str)
{
	int sign = 0;
	if(**str == '-' || **str == '+')
	{
		if(**str == '+')
			(*str)++;
		else
			while(**str == '-')
			{
				sign += 1;
				(*str)++;
        	}
	}
	return (sign);
}

unsigned int ft_atoi(char *str)
{
	unsigned int nbr;
	int	sign;
	int	is;

	nbr = 0;
	sign = 0;
	is = 0;
	while(*str && *str == ' ')
		str++;
	sign = ft_sign(&str);
	while(*str >= '0' && *str <= '9')
	{
		is = 1;
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	while(*str && *str == ' ')
		str++;
	if(sign == 2 && is == 0)
		return (0);
	else if(*str != '\0')
		return (255);
	if(sign % 2 == 0)
		return nbr;
	return (nbr * -1);
}

void	ft_exit(t_joins **head, t_env **env)
{
	t_env		*tmp;
	unsigned int nbr;
	int i;
	i = 1;

	tmp = ft_get_status_pos(*env, "?");
	while ((*head)->content[i])
		i++;
	if(i == 1)
	{
		t_env *tmp = ft_get_status_pos(*env, "?");
		ft_putstr("exit\n", 2);
		exit(ft_atoi4(tmp->value));
	}
	if(i != 2)
	{
		ft_putstr("Minishell$: exit: too many arguments\n", 2);
		ft_exit_status(env, "1");
		return ;
	}
	nbr = ft_atoi((*head)->content[1]);
	ft_lstclear_joins(head);
	ft_lstclear_env(env);
	char	*a = ft_itoa(nbr);
	ft_exit_status(env, a);
	free(a);
	exit(nbr);
}

t_env	*ft_get_status_pos(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (env);
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
	// if (is)
	// 	tmp->value = status;
	// else
	tmp->value = ft_strdup(status);
}
