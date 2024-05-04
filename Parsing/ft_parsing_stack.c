#include "../minishell.h"

int	ft_stack_words(t_words *words)
{
	int	i;

	i = 0;
	while (words)
	{
		if (words->type == 0)
			i++;
		else if (words->type == 2 || words->type == 1
			|| words->type == 4 || words->type == 5)
			words = words->next;
		if (words->type == 3)
			break ;
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

char	**ft_create_list(t_joins *stack_2, t_words **head)
{
	char	**dst;
	char	*err;
	int		words;
	int		i;

	words = ft_stack_words(*head);
	dst = (char **)malloc(sizeof(char *) * (words + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while ((*head) && (*head)->type != PIPE)
	{
		if (i < words)
			ft_check_word_type(stack_2, head, &i, dst);
		if (stack_2->in == -1 || stack_2->out == -1)
		{
			err = ft_strjoin("Minishell$ : ", (*head)->word);
			perror(err);
			free(err);
			while ((*head) && (*head)->type != PIPE)
				ft_next_node(head);
			break ;
		}
		ft_next_node(head);
	}
	return (dst[i] = NULL, dst);
}

t_joins	*ft_parse_stack(t_words **words)
{
	t_joins	*stack_2;
	t_joins	*new;

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
	t_joins *tmp = stack_2;
	while (tmp)
	{
		int i = 0;
		while (tmp->content[i])
		{
			printf("{%s}\n", tmp->content[i]);
			i++;
		}
		printf("in : {%d}\n", tmp->in);
		printf("out : {%d}", tmp->out);
		puts("\n|\n");
		tmp = tmp->next;
	}
	return (stack_2);
}
