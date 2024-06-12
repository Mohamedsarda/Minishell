#include "../minishell.h"

// static char	*check_after_env(char **tmp)
// {
// 	int		i;
// 	char	c;
// 	char	*str;

// 	i = 0;
// 	while (tmp[0][i])
// 	{
// 		c = check_key(tmp[0][i]);
// 		if (c)
// 		{
// 			str = ft_strlcpy(tmp, ft_get_env_len(*tmp, c));
// 			return (str);
// 		}
// 		i++;
// 	}
// 	return (*tmp);
// }
// static void	ft_norm____(char **str, char **tmp, t_env *env)
// {
// 	char	*a;
// 	char	*b;
// 	char	*c;
// 	char	*key;

// 	a = ft_strdup(*tmp);
// 	b = a;
// 	key = check_after_env(&a);
// 	if (ft_strcmp(key, a) == 0)
// 		*str = atest(key, env, *str);
// 	else
// 	{
// 		c = check_env(key, env);
// 		*str = test(*str, c);
// 		if (!c)
// 			free(c);
// 	}
// 	if (ft_strcmp(key, a) != 0)
// 	{
// 		*str = test(*str, a);
// 		free(key);
// 	}
// 	free(b);
// }
// static char	*ft_norm(char *content, t_env *env, char **tmp)
// {
// 	int		j;
// 	char	*str;

// 	j = -1;
// 	str = ft_strlcpy(&content, ft_get_env_len(content, '$'));
// 	if (content[0] == '\0')
// 		return (str);
// 	str = rm_single_qoutes(str);
// 	tmp = ft_split(content, '$');
// 	if (tmp == NULL || *tmp == NULL)
// 		return (NULL);
// 	while (tmp[++j])
// 	{
// 		if ((tmp[j][0] == '\"' || tmp[j][0] == '\'')
// 			&& check_double_qout(str) != 0)
// 			str = test(str, "$");
// 		ft_norm____(&str, &tmp[j], env);
// 		if (check_double_qout(str) == 0)
// 			str = rm_single_qoutes(str);
// 	}
// 	free_split(tmp);
// 	return (str);
// }


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
		while (s1[i])
		{
			dst[i] = s1[i];
			i++;
		}
	j = 0;
	if (s2)
		while (s2[j])
			dst[i++] = s2[j++];
	dst[i] = '\0';
	free(s1);
	return (dst);
}

char	*ft_text(char *result, char *str, int *i)
{
	int		j;
	int		c;
	char	*res;

	j = *i;
	c = 0;
	while (str[*i] && str[*i] != '$' && str[*i] != '\"' && str[*i] != '\'')
		(*i)++;
	res = malloc(ft_strlen(result) + (*i - j) + 1);
	while (result != NULL && result[c])
	{
		res[c] = result[c];
		c++;
	}
	while (str[j] && str[j] != '$' && str[j] != '\"' && str[j] != '\'')
	{
		res[c] = str[j];
		c++;
		j++;
	}
	res[c] = '\0';
	free(result);
	return (res);
}

char	*get_only_key(char *str, int *i)
{
	int		j;
	int		c;
	char	*res = NULL;

	j = *i;
	c = 0;
	if(str[*i] == '?')
		return ((*i)++, res = test_1(res, "?"));
	while (str[*i] && ((str[*i] >= 'a' && str[*i] <= 'z')
			|| (str[*i] >= 'A' && str[*i] <= 'Z')
			|| (str[*i] >= '0' && str[*i] <= '9') || str[*i] == '_'))
		(*i)++;
	res = malloc((*i - j) + 1);
	while (str[j] && ((str[j] >= 'a' && str[j] <= 'z')
			|| (str[j] >= 'A' && str[j] <= 'Z')
			|| (str[j] >= '0' && str[j] <= '9') || str[j] == '_'))
	{
		res[c] = str[j];
		c++;
		j++;
	}
	res[c] = '\0';
	return (res);
}


char	*ft_expand(char *result, char *str, int *i, t_env *env)
{
	char	*key;
	char	*sta;

	(*i)++;
	if (str[*i] == '\'' || str[*i] == '\"')
		return (result);
	else if (str[*i] >= '0' && str[*i] <= '9')
		return ((*i)++, result);
	else if (!str[*i])
		return (test_1(result, "$"));
	else if (str[*i] == '$')
		return ((*i)++, test_1(result, "$$"));
	else
	{
		key = get_only_key(str, i);
		sta = check_env(key, env);
		result = test_1(result, sta);
		free(key);
		return (result);
	}
	return (result);
}

char	*handle_single(char *result, char *str, int *i)
{
	int		j;
	char	*res;

	j = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	int		c;
	res = malloc((*i - j) + 1 + ft_strlen(result) + 2);
	c = 0;
	while (result != NULL && result[c])
	{
		res[c] = result[c];
		c++;
	}
	res[c++] = '\'';
	while (str[j] && str[j] != '\'')
	{
		res[c] = str[j];
		c++;
		j++;
	}
	res[c++] = '\'';
	res[c] = '\0';
	free(result);
	return (res);
}

char	*ft_text_doub(char *result, char *str, int *i)
{
	int		j;
	char	*res;
	int		c;

	j = *i;
	while (str[*i] && str[*i] != '$' && str[*i] != '\"')
		(*i)++;
	res = malloc(ft_strlen(result) + (*i - j) + 1);
	c = 0;
	while (result != NULL && result[c])
	{
		res[c] = result[c];
		c++;
	}
	while (str[j] && str[j] != '$' && str[j] != '\"')
	{
		res[c] = str[j];
		c++;
		j++;
	}
	res[c] = '\0';
	free(result);
	return (res);
}

int	check_sing(char *str, int *i)
{
	int	j;

	j = *i;
	j++;
	while (str[j])
	{
		if (str[j] == '\"')
			return (0);
		if (str[j] == '\'')
			return (1);
		j++;
	}
	return (0);
}

char	*ft_expand_doub_sing(char *result, char *str, int *i, t_env *env)
{
	char	*key;
	char	*sta;

	(*i)++;
	result = test_1(result, "\'");
	while (str[*i] != '\'' && str[*i] != '\"')
	{
		result = ft_text(result, str, i);
		if (str[*i] == '$')
		{
			if (str[*i + 1] == '\"')
				return ((*i)++, test_1(result, "$"));
			if (str[*i + 1] == '\'')
				return ((*i) += 2, test_1(result, "$\'"));
			else if (str[*i + 1] == '$')
			{
				result = test_1(result, "$$");
				(*i) += 2;
			}
			else
			{
				(*i)++;
				if (str[*i] >= '0' && str[*i] <= '9')
					return ((*i)++, test_1(result, "\'"));
				else
				{
					key = get_only_key(str, i);
					sta = check_env(key, env);
					free(key);
					result = test_1(result, sta);
					return (result);
				}
			}
		}
		else if(str[*i] == '\'')
			result = test(result, "\'");
		if (str[*i])
			(*i)++;
	}
	return (result);
}

char    *ft_expand_in_double(char *result, char *str, int *i, t_env *env)
{
	(*i)++;
	int j = 0;
	if (str[*i] >= '0' && str[*i] <= '9')
		return ((*i)++, result);
	else if (str[*i] == '\"' || str[*i] == '\'')
		return (test_1(result, "$"));
	else if(str[*i] == '$')
		return ((*i)++, test_1(result, "$$"));
	else if(str[*i] == ' ')
		return (test_1(result, "$"));
	else
	{
		int c = 0;
		char	*key = get_only_key(str, i);
		char *sta = check_env(key, env);
		char    *res = malloc(ft_strlen(sta) + 1 + ft_strlen(result));
		while (result != NULL && result[c])
		{
			res[c] = result[c];
			c++;
		}
		while(sta[j])
		{
			res[c] = sta[j];
			j++;
			c++;
		}
		res[c] = '\0';
		free(result);
		free(key);
		return (res);
	}
	return result;
}

char	*handle_double(char *result, char *str, int *i, t_env *env)
{
	(*i)++;

	result = test_1(result, "\"");
	while (str[*i] != '\"')
	{
		result = ft_text(result, str, i);
		if (str[*i] == '$' && !env->is)
			result = ft_expand_in_double(result, str, i, env);
		else if (str[*i] == '\'' && check_sing(str, i) == 1)
			result = ft_expand_doub_sing(result, str, i, env);
		else
			result = ft_text_doub(result, str, i);
		if(str[*i] == '$'  && env->is)
		{
			result = test_1(result, "$");
			(*i)++;
		}
	}
	if(result == NULL)
		result = test_1(result, "");
	result = test_1(result, "\"");
	return (result);
}

char	*all_expand(char *str, t_env *env)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	if (str[0] != '\'' && str[0] != '\"' && str[0] != '$')
		result = ft_text(result, str, &i);
	while (str[i])
	{
		if (str[i] && str[i] == '$' && !env->is)
			result = ft_expand(result, str, &i, env);
		if (str[i] && str[i] == '\'')
		{
			result = handle_single(result, str, &i);
			if (str[i])
				i++;
		}
		else if (str[i] && str[i] == '\"')
		{
			result = handle_double(result, str, &i, env);
			if (str[i] && (str[i] == '\'' || str[i] == '\"' || str[i] == '$'))
				i++;
			else
			{
				result = ft_text(result, str, &i);
				i++;
			}
		}
		else
			result = ft_text(result, str, &i);
	}
	return (result);
}

static char	*handle_type_6(char *content, t_env *env)
{
	char	*str;
	env->is = 0;
	str = all_expand(content, env);
	return (str);
}

char	*handle_env(t_words *node, char *content, t_env *env)
{
	char	*cont;

	(void)node;
	cont = handle_type_6(content, env);
	return (cont);
}
