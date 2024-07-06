#include "../minishell.h"

static int	strlen_no_quotes(char *str)
{
	int	i;
	int	res;

	((1) && (i = 0, res = 0));
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i++] != '\"')
				res++;
			i--;
		}
		else if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i++] != '\'')
				res++;
			i--;
		}
		else
			res++;
		if (str[i])
			i++;
	}
	return (res);
}

static void	dele_quotes_doub(char **str, int *i, int *j, char *res)
{
	(*i)++;
	while ((*str)[(*i)] && (*str)[(*i)] != '\"')
		res[(*j)++] = (*str)[(*i)++];
}

static void	dele_quotes_sing(char **str, int *i, int *j, char *res)
{
	(*i)++;
	while ((*str)[(*i)] && (*str)[(*i)] != '\'')
		res[(*j)++] = (*str)[(*i)++];
}

char	*dele_quotes(char **str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	res = malloc(strlen_no_quotes((*str)) + 1);
	if (res == NULL)
		return (NULL);
	while ((*str)[i])
	{
		if ((*str)[i] == '\"')
			dele_quotes_doub(str, &i, &j, res);
		else if ((*str)[i] == '\'')
			dele_quotes_sing(str, &i, &j, res);
		else
			res[j++] = (*str)[i];
		i++;
	}
	res[j] = '\0';
	return (free((*str)), res);
}
