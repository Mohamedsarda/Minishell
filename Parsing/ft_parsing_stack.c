
#include "../minishell.h"

int	ft_stack_words(t_words *words)
{
	int	i;

	i = 0;
	while (words)
	{
		if (words->type == 0) 
			i++;
		else if (words->type == 2 || words->type == 1 ||
			words->type == 4 || words->type == 5)
			words = words->next;
		if (words->type == 3)
			break ;
		words = words->next;
	}
	return (i);
}

char	*ft_putword(char *str)
{
	int		len;
	int		i;
	char	*dst;

	len = ft_strlen(str);
	i = 0;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	ft_next_node(t_words **head)
{
	t_words	*tmp;

	tmp = (*head)->next;
	free((*head)->word);
	free((*head));
	(*head) = tmp;
}

char	**ft_create_list(t_joins *stack_2, t_words **head)
{
	char	**dst;
	int		words;
	int		i;

	words = ft_stack_words(*head);
	printf("words : {%d}\n", words);
	dst = (char **)malloc(sizeof(char *) * (words + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while ((*head) && (*head)->type != PIPE)
	{
		if ((*head)->type == WORD)
		{
			dst[i] = ft_putword((*head)->word);
			i++;
			ft_next_node(head);
		}
		else if ((*head)->type == REDOU)
		{
			ft_next_node(head);
			stack_2->out = open((*head)->word, O_CREAT | O_WRONLY, 0777);
			ft_next_node(head);
		}
		else if ((*head)->type == REDIN)
		{
			ft_next_node(head);
			stack_2->in = open((*head)->word, O_CREAT | O_RDONLY, 0777);
			ft_next_node(head);
		}
		else if ((*head)->type == APPEND)
		{
			ft_next_node(head);
			stack_2->out = open((*head)->word, O_CREAT | O_RDWR | O_APPEND, 0777);
			ft_next_node(head);
		}
	}
	dst[i] = NULL;
	return (dst);
}

t_joins	*ft_lstnew_joins(t_words **words)
{
	t_joins *stack_2;

	stack_2 = (t_joins *)malloc(sizeof(t_joins));
	stack_2->in = 0;
	stack_2->out = 1;
	stack_2->content = ft_create_list(stack_2, words);
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

t_joins *ft_parse_stack(t_words **words)
{
	t_joins *stack_2;
	t_joins *new;

	stack_2 = ft_lstnew_joins(words);
	while ((*words))
	{
		if ((*words)->type == PIPE)
		{
			ft_next_node(words);
			new = ft_lstnew_joins(words);
			ft_lstaddback_joins(&stack_2, new);
		}
	}
	while (stack_2)
	{
		printf("{%s}\n", stack_2->content[0]);
		stack_2 = stack_2->next;
	}
	return (stack_2);
}