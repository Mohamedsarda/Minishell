#include "../minishell.h"

static char	*check_env(char *str, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			return (env->value);
		env = env->next;
	}
	return ("\0");
}

static char	check_key(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return ('\0');
	return (c);
}

static char	*check_after_env(char **tmp)
{
	int		i;
	char	c;
	char	*str;

	i = 0;
	while (tmp[0][i])
	{
		c = check_key(tmp[0][i]);
		if (c)
		{
			str = ft_strlcpy(tmp, ft_get_env_len(*tmp, c));
			return (str);
		}
		i++;
	}
	return (*tmp);
}

static char	*cpy(char	*str, int len)
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

char	*handle_env(t_words *node, char *content, t_env *env)
{
	char	*str;
	char	**tmp;
	int		j;
	char	*key;

	j = -1;
	if (node->type == 6)
	{
		str = ft_strlcpy(&content, ft_get_env_len(content, '$'));
		tmp = ft_split(content, '$');
		if (tmp == NULL || *tmp == NULL)
			return (NULL);
		while (tmp[++j])
		{
			key = check_after_env(&tmp[j]);
			if (ft_strcmp(key, tmp[j]) == 0)
			{
				if (key[0] >= '0' && key[0] <= '9')
					str = cpy(key, ft_strlen(key) - 1);
				else
					str = ft_strjoin(str, check_env(key, env));
			}
			else
			{
				str = ft_strjoin(str, check_env(key, env));
				if (ft_strcmp(key, tmp[j]) != 0)
					str = ft_strjoin(str, tmp[j]);
			}
			node->type = 0;
		}
		// free_split(tmp);
		return (str);
	}
	return (content);
}
