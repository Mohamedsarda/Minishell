#include "../minishell.h"

static int	ft_sign_1(const char str)
{
	if (str == '-')
		return (-1);
	return (1);
}

int	ft_atoi4(const char *str)
{
	long int	nbr;
	long int	nb;
	int			sign;

	nbr = 0;
	sign = 1;
	while ((*str == ' ' || *str == '\t' || *str == '\n'
			|| *str == '\v' || *str == '\f' || *str == '\r') && (str++));
	if (*str == '-' || *str == '+')
	{
		sign = ft_sign_1(*str);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nbr * 10 + (*str - '0');
		if (nbr > nb && sign == 1)
			return (-1);
		else if (nbr > nb && sign == -1)
			return (0);
		str++;
		nbr = nb;
	}
	return (nbr * sign);
}

void	multiple(char **str, int is)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str && *str && str[0][i])
	{
		if (is == 0 && str[0][i] == '\"')
		{
			i++;
			while (str[0][i] && str[0][i] != '\"')
				str[0][i++] *= -1;
		}
		else if (str[0][i] == '\'')
		{
			i++;
			while (str[0][i] && str[0][i] != '\'')
				str[0][i++] *= -1;
		}
		if (str[0][i] != '\0')
			i++;
	}
}

char	*test_1(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dst;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	dst = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dst)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			dst[i] = s1[i];
			i++;
		}
	}
	j = 0;
	if (s2)
		while (s2[j])
			dst[i++] = s2[j++];
	dst[i] = '\0';
	free(s1);
	return (dst);
}
