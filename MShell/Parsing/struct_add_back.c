#include "../minishell.h"

void	ft_lstadd_back_env(t_env **head, t_env *node)
{
	t_env	*last;

	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	if (!head || !node)
		return ;
	last = *head;
	if (last)
		while (last->next)
			last = last->next;
	last->next = node;
}

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
