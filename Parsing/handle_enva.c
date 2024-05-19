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



// new



char    *ft_text(char *result, char *str, int *i)
{
    int j = *i;
    while(str[*i] && str[*i] != '$' && str[*i] != '\"' && str[*i] != '\'')
        (*i)++;
    char    *res = malloc(ft_strlen(result) + (*i - j) + 1);

    int c = 0;
    while (result != NULL && result[c])
    {
        res[c] = result[c];
        c++;
    }
    while(str[j] && str[j] != '$' && str[j] != '\"' && str[j] != '\'')
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
    int j = *i;
    int c = 0;
    while(str[*i] && ((str[*i] >= 'a' && str[*i] <= 'z') ||
        (str[*i] >= 'A' && str[*i] <= 'Z') || (str[*i] >= '0' && str[*i] <= '9') || str[*i] == '_'))
            (*i)++;
    char    *res = malloc((*i - j) + 1);
	while(str[j] && ((str[j] >= 'a' && str[j] <= 'z') ||
        (str[j] >= 'A' && str[j] <= 'Z') || (str[j] >= '0' && str[j] <= '9') || str[j] == '_'))
    {
        res[c] = str[j];
        c++;
        j++;
    }
    res[c] = '\0';
    return res;
}

char    *ft_expand(char *result, char *str, int *i, t_env *env)
{
    (*i)++;
    int j = 0;
    if(str[*i] == '\'' || str[*i] == '\"')
        return result;
    else if (str[*i] >= '0' && str[*i] <= '9')
        return ((*i)++, result);
    else if  (!str[*i])
        return (result = test(result, "$"));
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
        // free(sta);
        free(key);
        return (res);
    }
    return result;
}

char    *handle_single(char *result, char *str, int *i)
{
    (*i)++;
    int j = *i;
    while (str[*i] && str[*i] != '\'')
        (*i)++;
    char    *res = malloc((*i - j) + 1 + ft_strlen(result));
    int c = 0;
    while (result != NULL && result[c])
    {
        res[c] = result[c];
        c++;
    }
    while(str[j] && str[j] != '\'')
    {
        res[c] = str[j];
        c++;
        j++;
    }
    res[c] = '\0';
    free(result);
    return (res);
}
char    *ft_text_doub(char *result, char *str, int *i)
{
    int j = *i;
    while(str[*i] && str[*i] != '$' && str[*i] != '\"')
        (*i)++;
    char    *res = malloc(ft_strlen(result) + (*i - j) + 1);

    int c = 0;
    while (result != NULL && result[c])
    {
        res[c] = result[c];
        c++;
    }
    while(str[j] && str[j] != '$' && str[j] != '\"')
    {
        res[c] = str[j];
        c++;
        j++;
    }
    res[c] = '\0';
    free(result);
    return (res);
}
char    *handle_double(char *result, char *str, int *i, t_env *env)
{
    (*i)++;
    char    *res = NULL;
    res = ft_text_doub(result, str, i);
    if(str[*i] != '\"')
        result = ft_expand(res, str, i, env);
    return (result);
}

char    *all_expand(char *str, t_env *env)
{
    char    *result = NULL;
    int    i = 0;

    if(str[0] != '\'' && str[0] != '\"' && str[0] != '$')
        result = ft_text(result, str, &i);
    while(str[i])
    {
        if(str[i] && str[i] == '$')
            result = ft_expand(result, str, &i, env);
        if(str[i] && str[i] == '\'')
        {
            result = handle_single(result, str, &i);
            if(str[i])
                i++;
        }
        else if(str[i] && str[i] == '\"')
        {
            result = handle_double(result, str, &i, env);
            if(str[i] && str[i] == '\'' && str[i] == '\"' && str[i] == '$')
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
	char	*str = all_expand(content, env);
	return (str);
}

char	*handle_env(t_words *node, char *content, t_env *env)
{
	char	*cont;
    (void)node;
    cont = handle_type_6(content, env);
    return (cont);
}
