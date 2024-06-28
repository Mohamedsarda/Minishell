#include "../minishell.h"

static size_t	ft_strlcpy_t(char *dst, char *src, size_t size)
{
	size_t	srclen;
	size_t	copy;

	srclen = ft_strlen(src);
	if (size > 0)
		copy = size - 1;
	else
		copy = 0;
	if (copy > srclen)
		copy = srclen;
	if (size > 0)
	{
		ft_memcpy(dst, src, copy);
		dst[copy] = '\0';
	}
	return (srclen);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	size_t	t_len;
	char	*t_str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && check_in_set(s1[start], set))
		start++;
	while (end > start && check_in_set(s1[end - 1], set))
		end--;
	t_len = end - start;
	t_str = (char *)malloc(t_len + 1);
	if (!t_str)
		return (NULL);
	ft_strlcpy_t(t_str, s1 + start, t_len + 1);
	free(s1);
	return (t_str);
}

int	quotes(char *str)
{
	int	a;
	int	b;
	int	i;

	a = 0;
	b = 0;
	i = 0;
	while (*str && str[i])
	{
		if (str[i] == '\"')
			a++;
		if (str[i] == '\'')
			b++;
		i++;
	}
	if (a % 2 != 0 || b % 2 != 0)
		return (0);
	else
		return (1);
}

char	*ft_rm_quotes(char *string, char c)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(string) - 1);
	if (!str)
		return (NULL);
	while (string[i])
	{
		if (string[i] == c)
		{
			while (string[++i] != c)
				str[j++] = string[i];
		}
		else
			str[j++] = string[i];
		i++;
	}
	str[j] = '\0';
	free(string);
	return (str);
}

void	ft_print_free(char *str, int fd)
{
	int	j;

	j = -1;
	while (str[++j])
		write(fd, &str[j], 1);
	free(str);
	write(fd, "\n", 1);
}
