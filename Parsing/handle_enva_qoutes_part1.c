#include "../minishell.h"

char	*rm_single_qoutes(char *str)
{
	char	*new_str;
	int		j;
	int		i;

	j = 0;
	i = 0;
	new_str = malloc(ft_strlen(str) + 1);
	while (str && str[i])
	{
		if (str[i] == '\'' && str[i + 1] == '\'')
			i += 2;
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

int	check_double_qout(char *str)
{
	while (*str)
	{
		if (*str == '\"')
			return (1);
		str++;
	}
	return (0);
}

char	*delete_double_qoutes(char *str)
{
	char	*new_str;
	int		j;
	int		i;

	j = 0;
	i = 0;
	new_str = malloc(ft_strlen(str) + 1);
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			while (str[i] && str[i] != '\"')
				new_str[j++] = str[i++];
			if (str[i] && str[i + 1] != '\0')
				new_str[j++] = str[i];
		}
		if (str[i] && str[i] != '\"')
			new_str[j++] = str[i];
		if (str[i] == '\0')
			break ;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*delete_qoutes(const char *str, char c)
{
	char	*new_str;
	int		j;
	int		i;

	j = 0;
	i = 0;
	new_str = malloc(ft_strlen_c(str, c) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != c)
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*delete_all_double_qoutes(char *str)
{
	char	*new_str;
	int		j;
	int		i;

	j = 0;
	i = 0;
	new_str = malloc(ft_strlen(str) + 1);
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			while (str[i] && str[i] != '\"')
				new_str[j++] = str[i++];
			if (str[i] && str[i + 1] != '\0' && str[i] != '\"')
				new_str[j++] = str[i];
		}
		if (str[i] && str[i] != '\"')
			new_str[j++] = str[i];
		if (str[i] == '\0')
			break ;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
