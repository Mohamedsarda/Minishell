#include "../minishell.h"

char	*befor_equal(char	*str)
{
	char	*key;
	int		i;

	i = 0;
	key = malloc(ft_strlen_key(str) + 1);
	if (!key)
		return (NULL);
	while (*str)
	{
		if (*str == '=')
			break ;
		if (*str == '+' && *(str + 1) == '=')
			break ;
		key[i] = *str;
		str++;
		i++;
	}
	key[i] = '\0';
	return (key);
}

int	ft_strlen_value(char *str)
{
	int	i;

	i = 0;
	while (*str && *str != '=' && *str != '+')
		str++;
	while (str[i])
		i++;
	return (i);
}

char	*after_equal(char	*str)
{
	char	*value;
	int		i;

	i = 0;
	if (!*str)
		return (NULL);
	value = malloc(ft_strlen_value(str) + 1);
	if (!value)
		return (NULL);
	while (*str && *str != '=' && *str != '+')
		str++;
	while (*str)
	{
		value[i] = *str;
		str++;
		i++;
	}
	value[i] = '\0';
	return (value);
}
