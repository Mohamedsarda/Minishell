#include "../minishell.h"

static int	ft_atoi1_check(char *str, int *i)
{
	if (str[(*i)] == '=')
		(*i)++;
	if (str[(*i)] == '-')
		return (-1);
	if (str[(*i)] == '+')
		(*i)++;
	return (1);
}

int	ft_atoi1(char *s)
{
	int	i;
	int	nmbr;

	i = 0;
	nmbr = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (ft_atoi1_check(s, &i) == -1)
		return (-1);
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			nmbr = nmbr * 10 + (s[i] - '0');
		else
			break ;
		i++;
	}
	if (s[i] != '\0' || nmbr > 999)
		return (9999);
	if (nmbr == 999)
		return (10000);
	return (nmbr);
}
