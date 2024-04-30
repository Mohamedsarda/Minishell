
#include "../minishell.h"

int	ft_stack_words(t_words *words)
{
	int	i;

	i = 0;
	while (words)
	{
		if (words->type == 0)
			i++;
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

char	**ft_create_list(t_words *head)
{
	char	**dst;
	int		words;
	int		i;

	words = ft_stack_words(head);
	dst = (char **)malloc(sizeof(char *) * (words + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < words && head)
	{
		if (head->type == 0)
		{
			dst[i] = ft_putword(head->word);
			i++;
		}
		else if (head)
		head = head->next;
	}
	dst[i] = NULL;
	return (dst);
}

t_joins *ft_parse_stack(t_words **words)
{
	// t_words *stack_1;
	t_joins *stack_2;
	// t_words *tmp;

	// stack_1 = *words;
	// stack_2 = NULL;
	int i = 0;
	// while (stack_1)
	// {
	// 	if (stack_1->type == 0)
	// 		i++;
	// 	stack_1 = stack_1->next;
	// }
	stack_2 = (t_joins *)malloc(sizeof(t_joins));
	stack_2->content = ft_create_list(*words);
	while (stack_2->content[i])
	{
		printf("{%s}\n", stack_2->content[i]);
		i++;
	}
	// printf("{%d}\n", i);
	// ft_lstclear(words);
	return (stack_2);
}