#include "../minishell.h"

void	ft_check_word_type(t_joins *stack_2, t_words **head, int *i, char **dst)
{
	char	**str;
	int		j;

	if ((*head)->type == WORD)
		dst[(*i)++] = ft_strdup((*head)->word);
	else if ((*head)->type == 6 && (*head)->word[0] != '\0')
	{
		if ((*head)->is == 1)
		{
			dst[(*i)++] = ft_strdup((*head)->word);
			return ;
		}
		str = ft_split((*head)->word, ' ');
		if (!str)
			return ;
		j = 0;
		while (str[j])
			dst[(*i)++] = ft_strdup(str[j++]);
		free_split(str);
	}
	else if ((*head)->type == 6 && (*head)->word[0] == '\0' && (*head)->is)
		dst[(*i)++] = ft_strdup((*head)->word);
	else if ((*head)->type == REDOU)
	{
		ft_next_node(head);
		if (ft_strlen((*head)->word) == 2 && (*head)->is == 1)
		{
			stack_2->out = -1;
			return ;
		}
		based_on_trim(&(*head)->word);
		stack_2->out = open((*head)->word, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	}
	else if ((*head)->type == REDIN)
	{
		ft_next_node(head);
		if (ft_strlen((*head)->word) == 2 && (*head)->is == 1)
		{
			stack_2->in = -1;
			return ;
		}
		based_on_trim(&(*head)->word);
		stack_2->in = open((*head)->word, O_RDONLY, 0777);
	}
	else if ((*head)->type == APPEND)
	{
		ft_next_node(head);
		if (ft_strlen((*head)->word) == 2 && (*head)->is == 1)
		{
			stack_2->out = -1;
			return ;
		}
		based_on_trim(&(*head)->word);
		stack_2->out = open((*head)->word, O_CREAT | O_RDWR | O_APPEND, 0777);
	}
	else if ((*head)->type == 7)
		ft_next_node(head);
}

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

int	ft_herd_while_2(t_joins *stack_2, t_words **head, t_env **env, char *str)
{
	char	*tmp;
	
	if ((*head)->is == 1 )
	{
		(*env)->is = 1;
		tmp = all_expand((*head)->word, *env);
	}
	if (!str
		|| (ft_strcmp(tmp, str) == 0
			|| ft_strcmp((*head)->word, str) == 0))
	{
		if ((*head)->is)
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
	if (!(*head)->is)
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
