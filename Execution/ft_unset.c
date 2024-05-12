#include "../minishell.h"

int	ft_search_key(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void    ft_unset(t_joins **head, t_env **env)
{
	int		i;
	t_env	*tmp;
	t_env	*cur;

	i = 1;
	while ((*head)->content[i])
	{
		tmp = (*env);
		while (tmp && ft_search_key(env, (*head)->content[i]))
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
