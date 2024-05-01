#include "../minishell.h"

int	check_length(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	if(i != 1)
		return (0);
	return (1);
	
}
int	hundle_error(t_words *words)
{
	t_words	*a;

	a = words;
	while (a)
	{
		if((a->type == 5 && check_length(a->word) == 0) || (a->type == 4 && check_length(a->word) == 0))
			return (0);
		if (a->type == REDOU || a->type == REDIN || a->type == PIPE
			|| a->type == HERD || a->type == APPEND || a->word != NULL)
		{
			if (!a->next)
				return (0);
			else if (a->next->type == REDOU || a->next->type == REDIN
				|| a->next->type == PIPE || a->next->type == HERD
				|| a->next->type == APPEND || a->next->word != NULL)
				return (0);
		}
		a = a->next;
	}
	return (1);
}