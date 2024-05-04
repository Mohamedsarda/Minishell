#include "../minishell.h"

static void	ft_lstdelone(t_words *lst)
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

static void	ft_lstdel_env(t_env *lst)
{
	if (!lst)
		return ;
	free(lst->key);
	free(lst->value);
	free(lst);
}

void	ft_lstclear_env(t_env **lst)
{
	t_env	*cur;

	if (!lst)
		return ;
	while (*lst)
	{
		cur = *lst;
		*lst = (*lst)->next;
		ft_lstdel_env(cur);
	}
}
