#include "../minishell.h"

void    ft_unset(t_joins **head, t_env **env)
{
	int		i;
	t_env	*tmp;
	t_env	*cur;

	tmp = (*env);
	i = 1;
	while ((*head)->content[i])
	{
		while (tmp)
		{
			cur = tmp;
			if (ft_strcmp((*head)->content[i], tmp->next->key) == 0)
			{
				if (tmp->next->next)
				cur->next = tmp->next->next;
				else
					cur->next = NULL;
				free(cur->key);
				free(cur->value);
				free(cur);
			}
			tmp = tmp->next;
		}
		i++;
	}
}
