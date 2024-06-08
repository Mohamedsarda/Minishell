#include "../minishell.h"

int	check_length(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i == 3)
		return (3);
	if (i != 2)
		return (0);
	return (1);
}

int	check_space(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	hundle_error(t_words *words)
{
	t_words	*a;
	int		len;

	a = words;
	len = check_length(a->word);
	if ((a->type == HERD && len >= 3))
		return (0);
	else if ((a->type == APPEND && len == 0) || (a->type == HERD && len == 0))
		return (0);
	if (a->type == REDOU || a->type == REDIN
		|| a->type == HERD || a->type == APPEND || a->word == NULL)
	{
		if (!a->next)
			return (0);
		if (a->next->word[0] == '\0'
			|| (a->next->is == 0 && a->next->type == 6
				&& check_space(a->next->word, ' ') == 1))
			return (10);
		else if (a->next->type == REDOU || a->next->type == REDIN
			|| a->next->type == PIPE || a->next->type == HERD
			|| a->next->type == APPEND || a->next->word == NULL)
			return (0);
	}
	if (a->type == PIPE)
	{
		if (!a->next)
			return (0);
		if (a->next->type == PIPE)
			return (0);
	}
	return (1);
}

void	ft_putstr(char *str, int fd)
{
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
}
