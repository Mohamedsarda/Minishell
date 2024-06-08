#include "../minishell.h"

int	ft_strlen_space(t_words *words)
{
	char	**dst;
	int		i;

	i = 0;
	dst = ft_split(words->word, ' ');
	if (!dst)
		return (0);
	while (dst[i])
		i++;
	free_split(dst);
	return (i);
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

char	**ft_create_list(t_joins *stack_2, t_words **head, t_env **env)
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
		if (i <= words)
		{
			if (hundle_error(*head) == 0)
			{
				printf("Minishell : syntax error near unexpected token\n");
				ft_lstclear(head);
				stack_2->error = 1;
				break ;
			}
			if (hundle_error(*head) == 10)
			{
				printf("Minishell : ambiguous redirect\n");
				ft_lstclear(head);
				stack_2->error = 1;
				break ;
			}
			if ((*head)->type == HERD)
				ft_handle_herd(stack_2, head, env);
			else
				ft_check_word_type(stack_2, head, &i, dst);
		}
		if (stack_2->in == -1 || stack_2->out == -1)
		{
			if (ft_strcmp("\'\'", (*head)->word) == 0
				|| ft_strcmp("\"\"", (*head)->word) == 0)
				printf("Minishell$: No such file or directory\n");
			else
			{
				err = ft_strjoin("Minishell$ : ", (*head)->word);
				perror(err);
				free(err);
			}
			while ((*head) && (*head)->type != PIPE)
				ft_next_node(head);
			break ;
		}
		ft_next_node(head);
	}
	return (dst[i] = NULL, dst);
}

t_joins	*ft_parse_stack(t_words **words, t_env **env)
{
	t_joins	*stack_2;
	t_joins	*new;
	t_joins	*tmp;
	int		i;

	stack_2 = ft_lstnew_joins(words);
	stack_2->content = ft_create_list(stack_2, words, env);
	while ((*words))
	{
		if ((*words)->type == PIPE)
		{
			if (!stack_2->content[0] && stack_2->in >= 2 && stack_2->out >= 2)
			{
				ft_putstr("Minishell$ :syntax error near unexpected token\n", 2);
				return (stack_2);
			}
			ft_next_node(words);
			new = ft_lstnew_joins(words);
			new->content = ft_create_list(new, words, env);
			if (stack_2 && !stack_2->content)
				return (stack_2);
			ft_lstaddback_joins(&stack_2, new);
		}
	}
	tmp = stack_2;
	while (tmp)
	{
		if (tmp->error)
			return (stack_2);
		tmp = tmp->next;
	}
	tmp = stack_2;
	if (tmp && !tmp->next)
	{
		i = 0;
		if (!tmp->content && !tmp->content[i])
			return (stack_2);
		if (tmp->in < 0 || tmp->out < 0)
			return (stack_2);
		ft_run_commad(&stack_2, env, tmp->content[0]);
	}
	else
		ft_is_pipe(&stack_2, env);
	return (stack_2);
}
