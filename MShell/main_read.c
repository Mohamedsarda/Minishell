#include "minishell.h"

int	check_qoutes(char *string)
{
	if (quotes(string) == 0)
	{
		ft_putstr("Minishell : unexpected ", 2);
		ft_putstr("EOF while looking for matching `\"'\n", 2);
		free(string);
		return (1);
	}
	return (0);
}

void	ft_string_nul(char *string, t_env **env_stack)
{
	t_env	*tmp;

	if (!string)
	{
		tmp = ft_get_status_pos(*env_stack, "?");
		exit(ft_atoi4(tmp->value));
	}
}

int	ft_is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i])
		return (1);
	else
		return (0);
}
