#include "../minishell.h"

void	conv_all(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str[0][i])
	{
		if (str[0][i] < 0)
		{
			if (i == 0)
				return ;
			str[0][i - 1] *= -1;
			while (str[0][i] < 0 && str[0][i])
				i++;
			i++;
			continue ;
		}
		str[0][i] *= -1;
		i++;
	}
}

void	conv_all_pos(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (*str && str[0][i])
	{
		str[0][i] *= -1;
		i++;
	}
}

void	convert_neg_to_po(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str[0][i])
	{
		if (str[0][i] < 0)
			str[0][i] *= -1;
		i++;
	}
}

int	check_qoutes(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (1);
		str++;
	}
	return (0);
}

int	check_nig(char	*str)
{
	while (*str)
	{
		if (*str < 0 && *(str - 1) == '\'')
			return (0);
		str++;
	}
	return (1);
}
