#include "../minishell.h"

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

t_env	*ft_get_status_pos(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (env);
}

int	ft_env_size(t_env *head)
{
	int	i;

	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

int	check_value(char *value)
{
	if (!value)
		return (-1);
	if (*value == '+' && *(value + 1) == '=')
		return (2);
	if (*value == '=')
		return (1);
	return (-1);
}

char	*delete_plus(char *str)
{
	char	*value;
	char	*tmp;
	int		i;

	i = 0;
	tmp = str;
	if (*tmp == '+')
		value = malloc(ft_strlen(tmp));
	else
		value = malloc(ft_strlen(tmp) + 1);
	if (!value)
		return (NULL);
	if (*tmp == '+')
		tmp += 1;
	while (*tmp)
	{
		value[i] = *tmp;
		tmp++;
		i++;
	}
	value[i] = '\0';
	free(str);
	return (value);
}
