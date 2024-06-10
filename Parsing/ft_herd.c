#include "../minishell.h"

char	*ft_env_eq(t_env **env, char *key)
{
	t_env	*head;

	head = (*env);
	if (*key && key[0] == '$')
	{
		while (head)
		{
			if (ft_strcmp(head->key, key + 1) == 0)
				return (head->value);
			head = head->next;
		}
	}
	return (key);
}

int	ft_herd_while_2(t_joins *stack_2, t_words *head, t_env **env, char *str)
{
	char	*tmp;
	
	if (head->is == 1 )
	{
		(*env)->is = 1;
		tmp = all_expand(head->word, *env);
	}
	if (!str
		|| (ft_strcmp(tmp, str) == 0
			|| ft_strcmp(head->word, str) == 0))
	{
		if (head->is)
			free(tmp);
		free(str);
		return (1);
	}
	if (!str)
	{
		free(str);
		write(stack_2->out, "\n", 1);
		return (2);
	}
	if (!head->is)
	{
		(*env)->is = 0;
		tmp = all_expand(str, *env);
		free(str);
		ft_print_free(tmp, stack_2->out);
	}
	else
	{
		free(tmp);
		ft_print_free(str, stack_2->out);
	}
	return (0);
}
