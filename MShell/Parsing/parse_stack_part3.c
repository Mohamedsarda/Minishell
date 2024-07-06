#include "../minishell.h"

static char	*ft_expand555(char *result, char *str, int *i, t_env *env)
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

static char	*ft_text44(char *result, char *str, int *i)
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

static char	*expand_herd(char *str, t_env **env)
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
		((1) && (tmp_2 = ft_strdup(head->word), tmp = dele_quotes(&tmp_2)));
	if (!str || ((head->is && ft_strcmp(tmp, str) == 0)
			|| ft_strcmp(head->word, str) == 0))
	{
		if (head->is)
			free(tmp);
		return (free(str), 1);
	}
	if (!str)
		return (free(str), write(stack_2->out, "\n", 1), 2);
	if (!head->is)
	{
		is = 0;
		tmp = expand_herd(str, env);
		ft_print_free(tmp, stack_2->out);
	}
	else
		(free(tmp), ft_print_free(str, stack_2->out));
	return (0);
}

int	ft_herd_while(t_joins *stack_2, t_words *head, t_env **env)
{
	char	*str;
	int		out;

	while (1)
	{
		str = readline("> ");
		if (!isatty(STDIN_FILENO))
		{
			dup2(STDIN_FILENO, open(ttyname(1), O_RDONLY, 0777));
			free(str);
			stack_2->in = -5;
			return (-1);
		}
		out = ft_herd_while_2(stack_2, head, env, str);
		if (out == 1)
			break ;
		else if (out == 2)
			break ;
	}
	return (0);
}
