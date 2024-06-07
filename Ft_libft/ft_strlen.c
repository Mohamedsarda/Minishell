#include "../minishell.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

static void	ft_lstdel_joins(t_joins *lst)
{
	int	i;

	if (!lst)
		return ;
	i = 0;
	if (lst->in > 2)
			close(lst->in);
	if (lst->out > 2)
		close(lst->out);
	while (lst && lst->content[i])
		free(lst->content[i++]);
	free(lst->content);
	free(lst);
}

void	ft_lstclear_joins(t_joins **lst)
{
	t_joins	*cur;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		cur = *lst;
		*lst = (*lst)->next;
		if (cur)
			ft_lstdel_joins(cur);
	}
}
