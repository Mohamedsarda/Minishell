#include "../minishell.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

static void	ft_lstdel_joins(t_joins *lst)
{
	int	i;

	if (!lst)
		return ;
	i = 0;
	while (lst && lst->content[i])
		free(lst->content[i++]);
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
