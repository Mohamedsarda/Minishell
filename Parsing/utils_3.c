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

static int	ft_num_len(long num)
{
	int		i;

	i = 0;
	if (num <= 0)
		num *= -1;
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		n_len;
	char	*str;
	long	num;

	num = n;
	n_len = ft_num_len(num);
	str = (char *)malloc((n_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[n_len--] = '\0';
	if (num == 0)
		str[0] = '0';
	if (num < 0)
		num *= -1;
	while (num > 0 && n_len >= 0)
	{
		str[n_len] = '0' + (num % 10);
		num /= 10;
		n_len--;
	}
	return (str);
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
