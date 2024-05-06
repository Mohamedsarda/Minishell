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

void	ft_norm____(char **str, char **tmp, t_env *env)
{
	char	*a;
	char	*b;
	char	*key;

	a = ft_strdup(*tmp);
	b = a;
	key = check_after_env(&a);
	if (*a == '\"')
	{
		*str = test(*str, "$");
	}
	else if (ft_strcmp(key, a) == 0)
		*str = atest(key, env, *str);
	else
		*str = test(*str, check_env(key, env));
	if (ft_strcmp(key, a) != 0)
	{
		*str = test(*str, a);
		free(key);
	}
	free(b);
}

char	*ft_norm(char *content, t_env *env, char **tmp)
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
		ft_norm____(&str, &tmp[j], env);
	}
	free_split(tmp);
	return (str);
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

char	*delete_double_qoutes(char *str)
{
	char	*new_str;
	int		j;
	int		i;

	j = 0;
	i = 0;
	new_str = malloc(ft_strlen(str) + 1);
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			while (str[i] && str[i] != '\"')
				new_str[j++] = str[i++];
			if (str[i] && str[i + 1] != '\0')
				new_str[j++] = str[i];
		}
		if (str[i] && str[i] != '\"')
			new_str[j++] = str[i];
		if (str[i] == '\0')
			break ;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
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

char	*delete_qoutes(const char *str, char c)
{
	char	*new_str;
	int		j;
	int		i;

	j = 0;
	i = 0;
	new_str = malloc(ft_strlen_c(str, c) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != c)
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
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

int	check_nig(char	*str)
{
	while (*str)
	{
		if (*str < 0)
			return (0);
		str++;
	}
	return (1);
}

void	conv_all(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str[0][i])
	{
		if (str[0][i] < 0)
		{
			if (i == 0)
				return ;
			str[0][i - 1] *= -1;
			while (str[0][i] < 0 && str[0][i])
				i++;
			i++;
			continue ;
		}
		str[0][i] *= -1;
		i++;
	}
}

void	conv_all_pos(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (*str && str[0][i])
	{
		str[0][i] *= -1;
		i++;
	}
}

void	convert_neg_to_po(char **str)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str[0][i])
	{
		if (str[0][i] < 0)
			str[0][i] *= -1;
		i++;
	}
}

int	check_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (1);
		str++;
	}
	return (0);
}

char	*type_6(char **content, t_env *env)
{
	char	**tmp;
	char	*cont;
	char	*str;

	tmp = NULL;
	multiple2(content);
	cont = delete_double_qoutes(*content);
	str = ft_norm(cont, env, tmp);
	free(cont);
	cont = delete_double_qoutes(str);
	free(str);
	if (!check_nig(cont))
	{
		conv_all(&cont);
		str = delete_qoutes(cont, '\'');
		free(cont);
		conv_all_pos(&str);
		return (str);
	}
	return (cont);
}

char	*handle_env(t_words *node, char *content, t_env *env)
{
	char	*str;
	char	*cont;

	if (node->type == 6)
	{
		if (content[1] == '\0')
		{
			node->type = 0;
			return (content);
		}
		cont = type_6(&content, env);
		node->type = 0;
		return (cont);
	}
	if (check_quotes(content) == 1)
	{
		multiple(&content, 0);
		cont = delete_qoutes(content, '\"');
		str = delete_qoutes(cont, '\'');
		free(cont);
		convert_neg_to_po(&str);
		return (str);
	}
	return (content);
}
