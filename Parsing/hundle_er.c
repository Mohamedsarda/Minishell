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

int	hundle_error(t_words *words)
{
	t_words	*a;
	int		len;

	a = words;
	while (a)
	{
		len = check_length(a->word);
		if ((a->type == 4 && len >= 3))
			return (0);
		else if ((a->type == 5 && len == 0) || (a->type == 4 && len == 0))
			return (0);
		if (a->type == REDOU || a->type == REDIN || a->type == PIPE
			|| a->type == HERD || a->type == APPEND || a->word == NULL)
		{
			if (!a->next)
				return (0);
			else if (a->next->type == REDOU || a->next->type == REDIN
				|| a->next->type == PIPE || a->next->type == HERD
				|| a->next->type == APPEND || a->next->word == NULL)
				return (0);
		}
		a = a->next;
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
