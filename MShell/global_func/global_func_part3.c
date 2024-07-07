#include "../minishell.h"

static int	check_in_set(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

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

t_env	*ft_get_status_pos(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (env);
}

void	free_split(char **tmp)
{
	int	i;

	i = 0;
	if (!tmp || !*tmp)
		return ;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
}
