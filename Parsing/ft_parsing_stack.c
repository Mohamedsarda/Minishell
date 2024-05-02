
#include "../minishell.h"

int	herd_g = 0;

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

void	ft_herd_sig(int i)
{
	(void)i;
	if (i == SIGINT)
	{
		write(1, "\n", 1);
		close(STDIN_FILENO);
        herd_g = 1;
	}
}

void	ft_check_word_type(t_joins *stack_2, t_words **head, int *i, char **dst)
{
	if ((*head)->type == WORD)
		dst[(*i)++] = ft_putword((*head)->word);
	else if ((*head)->type == REDOU)
	{
		ft_next_node(head);
		stack_2->out = open((*head)->word, O_CREAT | O_WRONLY, 0777);
	}
	else if ((*head)->type == REDIN)
	{
		ft_next_node(head);
		stack_2->in = open((*head)->word, O_RDONLY, 0777);
	}
	else if ((*head)->type == APPEND)
	{
		ft_next_node(head);
		stack_2->out = open((*head)->word, O_CREAT
				| O_RDWR | O_APPEND , 0777);
	}
	else if ((*head)->type == HERD)
	{
		char	*str;

		ft_next_node(head);
		stack_2->out = open(".herd_file", O_CREAT | O_WRONLY | O_TRUNC, 0777);
		rl_catch_signals = 0;
		while (1)
		{
			signal(SIGINT, ft_herd_sig);
			// printf("{%d}\n", herd_g);
			str = readline("> ");
			if (herd_g)
			{
				dup2(STDIN_FILENO, open(ttyname(1), O_RDONLY , 0777));
				free(str);
				str = NULL;
			}
			if (!str || ft_strcmp((*head)->word, str) == 0)
				break ;
			while (*str)
			{
				write(stack_2->out, str, 1);
				str++;
			}
			write(stack_2->out, "\n", 1);
		}
		close(stack_2->out);
		stack_2->in = open(".herd_file", O_CREAT | O_RDONLY , 0777);
	}
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

t_joins	*ft_lstnew_joins(t_words **words)
{
	t_joins	*stack_2;

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
	// while (stack_2)
	// {
	// 	int i = 0;
	// 	while (stack_2->content[i])
	// 	{
	// 		printf("{%s}\n", stack_2->content[i]);
	// 		i++;
	// 	}
	// 	printf("in : {%d}\n", stack_2->in);
	// 	printf("out : {%d}", stack_2->out);
	// 	puts("\n|\n");
	// 	stack_2 = stack_2->next;
	// }
	return (stack_2);
}
