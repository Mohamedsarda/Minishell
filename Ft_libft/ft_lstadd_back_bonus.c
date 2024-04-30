
#include "../minishell.h"

void	ft_lstadd_back(t_words **head, t_words *node)
{
	t_words	*last;

	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	if (!head || !node)
		return ;
	last = *head;
	while (last->next)
		last = last->next;
	last->next = node;
}
