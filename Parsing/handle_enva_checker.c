#include "../minishell.h"

char	*check_env(char *str, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			return (env->value);
		env = env->next;
	}
	return ("\0");
}

char	check_key(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return ('\0');
	return (c);
}

char	*cpy(char	*str, int len)
{
	int		i;
	char	*dst;

	i = 0;
	str++;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	while (i < len)
		dst[i++] = *str++;
	dst[i] = '\0';
	return (dst);
}

char	*atest(char *key, t_env *env, char *str)
{
	char	*a;
	char	*b;

	if (key[0] >= '0' && key[0] <= '9')
	{
		a = str;
		b = cpy(key, ft_strlen(key) - 1);
		str = ft_strjoin(str, b);
		free(b);
		free(a);
	}
	else
		str = test(str, check_env(key, env));
	return (str);
}
