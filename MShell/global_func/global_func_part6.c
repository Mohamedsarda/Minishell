#include "../minishell.h"

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

char	*get_only_key(char *str, int *i)
{
	int		j;
	int		c;
	char	*res;

	res = NULL;
	j = *i;
	c = 0;
	if (str[*i] == '?')
		return ((*i)++, res = test_1(res, "?"));
	while (str[*i] && ((str[*i] >= 'a' && str[*i] <= 'z')
			|| (str[*i] >= 'A' && str[*i] <= 'Z')
			|| (str[*i] >= '0' && str[*i] <= '9') || str[*i] == '_'))
		(*i)++;
	res = malloc((*i - j) + 1);
	if (!res)
		return (NULL);
	while (str[j] && ((str[j] >= 'a' && str[j] <= 'z')
			|| (str[j] >= 'A' && str[j] <= 'Z')
			|| (str[j] >= '0' && str[j] <= '9') || str[j] == '_'))
		res[c++] = str[j++];
	res[c] = '\0';
	return (res);
}

char	*check_env(char *str, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(str, env->key))
			return (env->value);
		env = env->next;
	}
	return ("\0");
}

void	ft_exit_status(t_env **env, char *status)
{
	t_env	*tmp;

	tmp = (*env);
	tmp = ft_get_status_pos(tmp, "?");
	if (!tmp)
		return ;
	free(tmp->value);
	tmp->value = NULL;
	tmp->value = ft_strdup(status);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	if (n == 0)
		return (0);
	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((i < n - 1) && (str1[i] && str2[i]) && (str1[i] == str2[i]))
		i++;
	return (str1[i] - str2[i]);
}
