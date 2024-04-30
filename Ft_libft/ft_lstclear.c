#include "../minishell.h"

void	ft_lstdelone(t_words *lst)
{
	if (!lst)
		return ;
	free(lst->word);
	free(lst);
}

void	ft_lstclear(t_words **lst)
{
	t_words	*cur;

	if (!lst)
		return ;
	while (*lst)
	{
		cur = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(cur);
	}
}