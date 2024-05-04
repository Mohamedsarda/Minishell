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

void	ft_lstdel_env(t_env *lst)
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

void	ft_lstdel_joins(t_joins *lst)
{
	int	i;

	if (!lst)
		return ;
	i = -1;
	while (lst->content[++i])
		free(lst->content[i]);
	free(lst->content);
	free(lst);
}

void	ft_lstclear_joins(t_joins **lst)
{
	t_joins	*cur;

	if (!lst)
		return ;
	while (*lst)
	{
		cur = *lst;
		*lst = (*lst)->next;
		ft_lstdel_joins(cur);
	}
}
