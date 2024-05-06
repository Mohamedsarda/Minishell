#include "../minishell.h"

char	*test(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	dst = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dst)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
	free(s1);
	return (dst);
}

char	*add_one(char *s1, char s2)
{
	int		i;
	char	*dst;

	i = 0;
	dst = (char *)malloc(ft_strlen(s1) + 2);
	if (!dst)
		return (NULL);
	while (s1 && s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i++] = s2;
	dst[i] = '\0';
	free(s1);
	return (dst);
}

int	ft_strlen_c(const char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
			j++;
		i++;
	}
	return (i);
}

void	multiple2(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (*str && str[0][i])
	{
		if (str[0][i] == '\"')
		{
			i++;
			while (str[0][i] && str[0][i] != '\"')
				i++;
		}
		else if (str[0][i] == '\'')
		{
			i++;
			while (str[0][i] && str[0][i] != '\'')
			{
				str[0][i] *= -1;
				i++;
			}
		}
		i++;
	}
}
