#include "../minishell.h"

char	*all_expand(char *str, t_env *env)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	if (str[0] != '\'' && str[0] != '\"' && str[0] != '$')
		result = ft_text_only(result, str, &i);
	while (str[i])
	{
		if (str[i] && str[i] == '$' && !env->is)
			result = ft_expand(result, str, &i, env);
		result = ft_other(result, str, &i, env);
	}
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

char	*ft_other(char *result, char *str, int *i, t_env *env)
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
