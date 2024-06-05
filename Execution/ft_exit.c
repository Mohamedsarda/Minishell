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
	unsigned int nbr;
	int i;
	ft_lstclear_env(env);
	i = 1;
	while ((*head)->content[i])
		i++;
	if(i != 2)
	{
		printf("bash: exit: too many arguments\n");
		return ;
	}
	nbr = ft_atoi((*head)->content[1]);
	ft_lstclear_joins(head);
	exit(nbr);
}

t_env	*ft_get_status_pos(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "?") == 0)
			return env;
		env = env->next;
	}
	return env;
}

void	ft_exit_status(t_env **env, char *status)
{
	t_env	*tmp;

	tmp = (*env);
	tmp = ft_get_status_pos(tmp);
	free(tmp->value);
	tmp->value = NULL;
	tmp->value = ft_strdup(status);
	// printf("%s:%s\n", tmp->key, tmp->value);
	// puts("++++++");
}
