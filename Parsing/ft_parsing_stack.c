
#include "../minishell.h"

int	ft_stack_words(t_words *words)
{
	int	i;
	// int	flag;

	i = 0;
	// flag = 0;
	while (words)
	{
		if (words->type == 0) 
			i++;
		else if (words->type == 2)
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
	// t_words	*tmp;

	words = ft_stack_words(*head);
	printf("words : {%d}\n", words);
	dst = (char **)malloc(sizeof(char *) * (words + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while ((*head))
	{
		if ((*head)->type == 0)
		{
			dst[i] = ft_putword((*head)->word);
			i++;
			ft_next_node(head);
		}
		else if ((*head)->type == 2)
		{
			ft_next_node(head);
			stack_2->out = open((*head)->word, O_CREAT | O_WRONLY, 0777);
			ft_next_node(head);
		}
		else if ((*head)->type == 1)
		{
			ft_next_node(head);
			stack_2->in = open((*head)->word, O_CREAT | O_RDONLY, 0777);
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
	return (stack_2);
}

t_joins *ft_parse_stack(t_words **words)
{
	t_joins *stack_2;

	int i = 0;
	stack_2 = ft_lstnew_joins(words);
	while (stack_2->content[i])
	{
		printf("{%s}\n", stack_2->content[i]);
		i++;
	}
	printf("in : %d\n", stack_2->in);
	printf("out : %d\n", stack_2->out);
	// ft_lstclear(words);
	return (stack_2);
}