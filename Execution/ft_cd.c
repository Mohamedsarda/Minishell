#include "../minishell.h"

void	ft_cd(t_joins **head)
{
	// t_joins	*tmp;

	// tmp = (*head)->next;
	if (chdir((*head)->content[1]) != 0)
		perror("Minishell$ ");
	ft_lstclear_joins(head);
}
