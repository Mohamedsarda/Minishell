
#include "../minishell.h"

int	hundle_error(t_words *words)
{
	t_words *a = words;
	while(a)
	{
		if(a->type == REDOU || a->type == REDIN || a->type == PIPE || a->type == HERD || a->type == APPEND)
        {
		    if(a->type == REDOU || a->type == REDIN || a->type == PIPE || a->type == HERD || a->type == APPEND)
                return (0);
        }
		a = a->next;
	}
	return (1);
}