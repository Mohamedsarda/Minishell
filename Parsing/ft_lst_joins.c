#include "../minishell.h"

t_joins	*ft_lstnew_joins(t_words **words)
{
	t_joins	*stack_2;

	(void)words;
	stack_2 = (t_joins *)malloc(sizeof(t_joins));
	stack_2->in = 0;
	stack_2->out = 1;
	stack_2->error = 0;
	stack_2->quotes = 0;
	stack_2->content = NULL;
	stack_2->next = NULL;
	return (stack_2);
}

void	ft_lstaddback_joins(t_joins **head, t_joins *node)
{
	t_joins	*last;

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
