#include "../minishell.h"

char	*conv_str_ne(char	*str, int len)
{
	int		i;
	char	*dst;

	i = 0;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	while (i < len)
		dst[i++] = *str++;
	dst[i] = '\0';
	return (dst);
}

char	*add_sing_qou(char *str)
{
	char	*cont;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cont = malloc(ft_strlen(str) + 3);
	if (!cont)
		return (NULL);
	cont[j++] = '\'';
	while (str[i])
	{
		cont[j] = str[i];
		i++;
		j++;
	}
	cont[j++] = '\'';
	cont[j++] = '\0';
	free(str);
	return (cont);
}

char	*check_env(char *str, t_env *env)
{
	int		i;
	char	*cont;

	i = 0;
	while (env)
	{
		if (!ft_strcmp(str, env->key))
		{
			while (env->value[i])
			{
				if (env->value[i] == '\"')
				{
					cont = conv_str_ne(env->value, ft_strlen(env->value));
					conv_all_pos(&cont);
					cont = add_sing_qou(cont);
					return (cont);
				}
				i++;
			}
			return (env->value);
		}
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
	char	*c;

	if (key[0] >= '0' && key[0] <= '9')
	{
		a = str;
		b = cpy(key, ft_strlen(key) - 1);
		str = ft_strjoin(str, b);
		free(b);
		free(a);
	}
	else
	{
		c = check_env(key, env);
		str = test(str, c);
		if (!c)
			free(c);
	}
	return (str);
}
