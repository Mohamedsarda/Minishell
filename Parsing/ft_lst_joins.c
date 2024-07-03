#include "../minishell.h"

t_joins	*ft_lstnew_joins(t_words **words)
{
	t_joins	*stack_2;

	(void)words;
	stack_2 = (t_joins *)malloc(sizeof(t_joins));
	if (!stack_2)
		return (NULL);
	stack_2->in = 0;
	stack_2->out = 1;
	stack_2->error = 0;
	stack_2->quotes = 0;
	stack_2->content = NULL;
	stack_2->next = NULL;
	return (stack_2);
}

void	ft_lstaddback_joins(t_joins **head, t_joins *node)
{
	t_joins	*last;

	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	if (!head || !node)
		return ;
	last = *head;
	while (last->next)
		last = last->next;
	last->next = node;
}

int	ft_stack_words(t_words *words)
{
	int	i;

	i = 0;
	while (words)
	{
		if (words->type == 0)
			i++;
		if (words->type == 6 && words->word[0] != '\0')
		{
			if (words->is == 1)
				i++;
			else
				i += ft_strlen_space(words);
		}
		else if (words->type == 6 && words->word[0] == '\0' && words->is)
			i++;
		else if (words->type == 2 || words->type == 1
			|| words->type == 4 || words->type == 5)
			words = words->next;
		if (words != NULL && words->type == 3)
			break ;
		if (words != NULL)
			words = words->next;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	dst = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dst)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		dst[i++] = s2[j++];
	dst[i] = '\0';
	return (dst);
}
