#include "../minishell.h"

void    ft_unset(t_joins **head, t_env **env)
{
	int		i;
	t_env	*tmp;
	t_env	*cur;

	i = 1;
	while ((*head)->content[i])
	{
		tmp = (*env);
		while (tmp)
		{
			cur = tmp->next;
			if (ft_strcmp((*head)->content[i], cur->key) == 0)
			{
				tmp->next = cur->next;
				free(cur->key);
				free(cur->value);
				free(cur);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	ft_lstclear_joins(head);
}
