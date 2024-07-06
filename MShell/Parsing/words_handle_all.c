#include "../minishell.h"

static char	*ft_expand(char *result, char *str, int *i, t_env *env)
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

static char	*ft_text_doub(char *result, char *str, int *i)
{
	int		j;
	char	*res;
	int		c;

	j = *i;
	while (str[*i] && str[*i] != '$' && str[*i] != '\"')
		(*i)++;
	res = malloc(ft_strlen(result) + (*i - j) + 1);
	if (!res)
		return (NULL);
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

static char	*handle_double(char *result, char *str, int *i, t_env *env)
{
	(*i)++;
	result = test_1(result, "\"");
	while (str[*i] != '\"')
	{
		result = ft_text_only(result, str, i);
		if (str[*i] == '$')
			result = ft_expand_in_double(result, str, i, env);
		else
			result = ft_text_doub(result, str, i);
	}
	if (result == NULL)
		result = test_1(result, "");
	result = test_1(result, "\"");
	return (result);
}

static char	*ft_other(char *result, char *str, int *i, t_env *env)
{
	if (str[(*i)] && str[(*i)] == '\'')
	{
		result = handle_single_parssing(result, str, i);
		if (str[(*i)])
			(*i)++;
	}
	else if (str[(*i)] && str[(*i)] == '\"')
	{
		result = handle_double(result, str, i, env);
		if (str[(*i)])
			(*i)++;
	}
	else
		result = ft_text_only(result, str, &(*i));
	return (result);
}

char	*handle_env(t_words *node, char *content, t_env *env)
{
	char	*result;
	int		i;

	(void)node;
	i = 0;
	result = NULL;
	if (content[0] != '\'' && content[0] != '\"' && content[0] != '$')
		result = ft_text_only(result, content, &i);
	while (content[i])
	{
		if (content[i] && content[i] == '$' && !env->is)
			result = ft_expand(result, content, &i, env);
		result = ft_other(result, content, &i, env);
	}
	return (result);
}
