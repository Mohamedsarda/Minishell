#include "../minishell.h"

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

// char	*ft_expand_doub_sing(char *result, char *str, int *i, t_env *env)
// {
// 	char	*key;
// 	char	*sta;
// 
// 	(*i)++;
// 	result = test_1(result, "\'");
// 	while (str[*i] != '\'' && str[*i] != '\"')
// 	{
// 		result = ft_text_only(result, str, i);
// 		if (str[*i] == '$')
// 		{
// 			if (str[*i + 1] == '\"')
// 				return ((*i)++, test_1(result, "$"));
// 			if (str[*i + 1] == '\'')
// 				return ((*i) += 2, test_1(result, "$\'"));
// 			else if (str[*i + 1] == '$')
// 			{
// 				result = test_1(result, "$$");
// 				(*i) += 2;
// 			}
// 			else
// 			{
// 				(*i)++;
// 				if (str[*i] >= '0' && str[*i] <= '9')
// 					return ((*i)++, test_1(result, "\'"));
// 				else
// 				{
// 					key = get_only_key(str, i);
// 					sta = check_env(key, env);
// 					free(key);
// 					result = test_1(result, sta);
// 					return (result);
// 				}
// 			}
// 		}
// 		else if (str[*i] == '\'')
// 			result = test(result, "\'");
// 		if (str[*i])
// 			(*i)++;
// 	}
// 	return (result);
// }

char	*real_expand_in_double(char *str, int *i, t_env *env, char *result)
{
	char	*key;
	char	*sta;
	char	*res;
	int		c;
	int		j;

	c = 0;
	j = 0;
	key = get_only_key(str, i);
	sta = check_env(key, env);
	res = malloc(ft_strlen(sta) + 1 + ft_strlen(result));
	if (!res)
		return (NULL);
	while (result != NULL && result[c])
	{
		res[c] = result[c];
		c++;
	}
	while (sta[j])
		res[c++] = sta[j++];
	res[c] = '\0';
	free(key);
	return (res);
}

char	*ft_text_only(char *result, char *str, int *i)
{
	int		j;
	int		c;
	char	*res;

	j = *i;
	c = 0;
	while (str[*i] && str[*i] != '$' && str[*i] != '\"' && str[*i] != '\'')
		(*i)++;
	res = malloc(ft_strlen(result) + (*i - j) + 1);
	if (!res)
		return (NULL);
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
