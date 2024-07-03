#include "../minishell.h"


char	*handle_single(char *result, char *str, int *i)
{
	int		j;
	char	*res;
	int		c;

	j = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	res = malloc((*i - j) + 1 + ft_strlen(result) + 2);
	if (!res)
		return (NULL);
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

char	*ft_expand_in_double(char *result, char *str, int *i, t_env *env)
{
	char	*res;

	res = NULL;
	(*i)++;
	if (str[*i] >= '0' && str[*i] <= '9')
		return ((*i)++, result);
	else if (str[*i] == '\"' || str[*i] == '\'')
		return (test_1(result, "$"));
	else if (str[*i] == '$')
		return ((*i)++, test_1(result, "$$"));
	else if (str[*i] == ' ')
		return (test_1(result, "$"));
	else
	{
		res = real_expand_in_double(str, i, env, result);
		free(result);
		return (res);
	}
	return (result);
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
		if (str[*i] == '$' && env->is)
		{
			result = test_1(result, "$");
			(*i)++;
		}
	}
	if (result == NULL)
		result = test_1(result, "");
	result = test_1(result, "\"");
	return (result);
}
