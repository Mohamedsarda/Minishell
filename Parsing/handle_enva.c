#include "../minishell.h"

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

static void	ft_norm____(char **str, char **tmp, t_env *env)
{
	char	*a;
	char	*b;
	char	*c;
	char	*key;

	a = ft_strdup(*tmp);
	b = a;
	key = check_after_env(&a);
	if (ft_strcmp(key, a) == 0)
		*str = atest(key, env, *str);
	else
	{
		c = check_env(key, env);
		*str = test(*str, c);
		if (!c)
			free(c);
	}
	if (ft_strcmp(key, a) != 0)
	{
		*str = test(*str, a);
		free(key);
	}
	free(b);
}

static char	*ft_norm(char *content, t_env *env, char **tmp)
{
	int		j;
	char	*str;

	j = -1;
	str = ft_strlcpy(&content, ft_get_env_len(content, '$'));
	if (content[0] == '\0')
		return (str);
	str = rm_single_qoutes(str);
	tmp = ft_split(content, '$');
	if (tmp == NULL || *tmp == NULL)
		return (NULL);
	while (tmp[++j])
	{
		if ((tmp[j][0] == '\"' || tmp[j][0] == '\'')
			&& check_double_qout(str) != 0)
			str = test(str, "$");
		ft_norm____(&str, &tmp[j], env);
		if (check_double_qout(str) == 0)
			str = rm_single_qoutes(str);
	}
	free_split(tmp);
	return (str);
}

static char	*handle_type_6(char **content, t_env *env)
{
	char	**tmp;
	char	*cont;
	char	*str;

	tmp = NULL;
	multiple2(content);
	cont = ft_strdup(*content);
	str = ft_norm(cont, env, tmp);
	free(cont);
	cont = delete_all_double_qoutes(str);
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
		cont = handle_type_6(&content, env);
		// node->type = 0;
		return (cont);
	}
	if (check_qoutes(content) == 1)
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
