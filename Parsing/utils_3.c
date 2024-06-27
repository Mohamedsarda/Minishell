#include "../minishell.h"

void	based_on_trim(char **str)
{
	if (*str[0] == '\"')
		*str = ft_strtrim(*str, "\"");
	else if (*str[0] == '\'')
		*str = ft_strtrim(*str, "\'");
}

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_intlen(int n)
{
	int	nbdg;
	int	tmp;

	nbdg = 0;
	tmp = n;
	while (tmp != 0)
	{
		tmp /= 10;
		nbdg++;
	}
	return (nbdg);
}

static char	*zero(void)
{
	char	*arr;

	arr = malloc(2 * sizeof(char));
	if (arr == NULL)
		return (NULL);
	arr[0] = '0';
	arr[1] = '\0';
	return (arr);
}

static void	fillarr(char *res, int n, int nbrdg, int isnegative)
{
	int	index;
	int	digit;

	index = nbrdg - 1;
	while (n != 0)
	{
		if (n < 0)
			digit = -(n % 10);
		else
			digit = n % 10;
		res[index] = digit + '0';
		n /= 10;
		index--;
	}
	if (isnegative != 0)
		res[0] = '-';
	res[nbrdg] = '\0';
}

char	*ft_itoa(int n)
{
	int		nbrdg;
	int		isnegative;
	char	*res;

	if (n == 0)
		return (zero());
	nbrdg = ft_intlen(n);
	isnegative = 0;
	if (n < 0)
	{
		isnegative = 1;
		nbrdg++;
	}
	res = malloc((nbrdg + 1) * sizeof(char));
	if (!res)
		return (NULL);
	fillarr(res, n, nbrdg, isnegative);
	return (res);
}

int	check_in_set(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}
