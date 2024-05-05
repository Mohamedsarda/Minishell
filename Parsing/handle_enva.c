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
	return ('c');
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
char *atest(char *key, t_env *env, char *str)
{
	if (key[0] >= '0' && key[0] <= '9')
	{
		char *a = str;
		char	*b = cpy(key, ft_strlen(key) - 1);
		str = ft_strjoin(str, b);
		free(b);
		free(a);
	}
	else
	{
		free(str);
		str = ft_strjoin(str, check_env(key, env));
	}
	return (str);
}

void ft_norm____(char **str, char **tmp, char *key, t_env *env)
{
	char	*a;
	char	*b;

	a = ft_strdup(*tmp);
	b = a;
	key = check_after_env(&a);
	if (ft_strcmp(key, a) == 0)
		*str = atest(key, env, *str);
	else
	{
		*str = test(*str, check_env(key, env));
		if (ft_strcmp(key, a) != 0)
			*str = test(*str, a);
	}
	free(b);
	if (ft_strcmp(key, a) != 0)
		free(key);
}

char	*ft_norm(char *content , t_env *env ,char **tmp , char *key)
{
	int		j;
	char	*str;

	j = -1;
	str = ft_strlcpy(&content, ft_get_env_len(content, '$'));
	if (content[0] == '\0')
		return (str);
	tmp = ft_split(content, '$');
	if (tmp == NULL || *tmp == NULL)
		return (NULL);
	while (tmp[++j])
	{
		ft_norm____(&str, &tmp[j], key, env);
	}
	free_split(tmp);
	return (str);
}

char	*handle_env(t_words *node, char *content, t_env *env)
{
	char	*str;
	char	*key;
	char	**tmp;

	key = NULL;
	tmp = NULL;
	if (node->type == 6)
	{
		// split_arr(content);
		// multiple(&content, 1);
		str = ft_norm(content, env, tmp, key);
		// str = ft_rm_quotes(str, '\'');
		// str = ft_rm_quotes(str, '\"');
		// multiple(&str, 0);
		node->type = 0;
		return (str);
	}
	return (content);
}
