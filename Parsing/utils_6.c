#include "../minishell.h"

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

char	*get_only_key(char *str, int *i)
{
	int		j;
	int		c;
	char	*res;

	res = NULL;
	j = *i;
	c = 0;
	if (str[*i] == '?')
		return ((*i)++, res = test_1(res, "?"));
	while (str[*i] && ((str[*i] >= 'a' && str[*i] <= 'z')
			|| (str[*i] >= 'A' && str[*i] <= 'Z')
			|| (str[*i] >= '0' && str[*i] <= '9') || str[*i] == '_'))
		(*i)++;
	res = malloc((*i - j) + 1);
	if (!res)
		return (NULL);
	while (str[j] && ((str[j] >= 'a' && str[j] <= 'z')
			|| (str[j] >= 'A' && str[j] <= 'Z')
			|| (str[j] >= '0' && str[j] <= '9') || str[j] == '_'))
		res[c++] = str[j++];
	res[c] = '\0';
	return (res);
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
