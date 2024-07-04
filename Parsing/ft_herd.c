#include "../minishell.h"

char	*ft_remove_qoutes_herd(char *str)
{
	char	*dst;
	int		i;
	int		j;

	i = 1;
	j = 0;
	dst = malloc(ft_strlen(str) - 1);
	if (!dst)
		return (NULL);
	while (str && str[i] && str[i + 1] != '\0')
		dst[j++] = str[i++];
	dst[j] = '\0';
	free(str);
	return (dst);
}

char	*ft_text44(char *result, char *str, int *i)
{
	int		j;
	int		c;
	char	*res;

	j = *i;
	c = 0;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	res = malloc(ft_strlen(result) + (*i - j) + 1);
	if (!res)
		return (NULL);
	while (result != NULL && result[c])
	{
		res[c] = result[c];
		c++;
	}
	while (str[j] && str[j] != '$')
	{
		res[c] = str[j];
		c++;
		j++;
	}
	res[c] = '\0';
	free(result);
	return (res);
}

char	*ft_expand555(char *result, char *str, int *i, t_env *env)
{
	char	*key;
	char	*sta;

	(*i)++;
	if (str[*i] == '\'' || str[*i] == '\"' || !str[*i])
		return (test_1(result, "$"));
	else if (str[*i] >= '0' && str[*i] <= '9')
		return ((*i)++, result);
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

char	*expand_herd(char *str, t_env **env)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	if (str[0] != '\0' && str[0] != '$')
		result = ft_text44(result, str, &i);
	while (str[i])
	{
		if (str[i] && str[i] == '$')
			result = ft_expand555(result, str, &i, *env);
		else
			result = ft_text44(result, str, &i);
	}
	free(str);
	return (result);
}

int	ft_herd_while_2(t_joins *stack_2, t_words *head, t_env **env, char *str)
{
	char	*tmp;
	char	*tmp_2;
	int		is;

	if (head->is == 1)
	{
		tmp_2 = ft_strdup(head->word);
		tmp = dele_quotes(&tmp_2);
	}
	if (!str
		|| ((head->is && ft_strcmp(tmp, str) == 0)
			|| ft_strcmp(head->word, str) == 0))
	{
		if (head->is)
			free(tmp);
		free(str);
		return (1);
	}
	if (!str)
	{
		free(str);
		write(stack_2->out, "\n", 1);
		return (2);
	}
	if (!head->is)
	{
		is = 0;
		tmp = expand_herd(str, env);
		ft_print_free(tmp, stack_2->out);
	}
	else
	{
		free(tmp);
		ft_print_free(str, stack_2->out);
	}
	return (0);
}
