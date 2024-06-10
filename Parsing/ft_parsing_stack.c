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

int	ft_words(t_words *head)
{
	int i = 0;
	
	while (head)
	{
		if (head->type == PIPE)
			return (i);
		if (head->type == HERD)
		{
			if(head)
				head = head->next;
			if(head)
				head = head->next;
			continue;
		}
		i++;
		if(head)
			head = head->next;
	}
	return (i);
}

char	**ft_create_list(t_joins *stack_2, t_words *head, t_env **env)
{
	char	**dst;
	int		words;
	int		i;

	words = ft_words(head);
	dst = (char **)malloc(sizeof(char *) * (words + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (head && head->type != PIPE)
	{
		if (i <= words)
		{
			if (hundle_error(head) == 0)
			{
				printf("Minishell : syntax error near unexpected token\n");
				stack_2->error = 1;
				break ;
			}
			if (hundle_error(head) == 10)
			{
				printf("Minishell : ambiguous redirect\n");
				stack_2->error = 1;
				break ;
			}
			if (head->type == HERD)
			{
				ft_handle_herd(stack_2, head, env);
				head = head->next;
			}
			else
				dst[i++] = ft_strdup(head->word);
		}
		head = head->next;
	}
	return (dst[i] = NULL, dst);
}

int	ft_syntax_error(t_joins *node, t_words **words)
{
	if (!node->content[0] && (node->in == 0 && node->out == 1) && !node->error)
	{
		ft_putstr("Minishell$ :syntax error near unexpected token\n", 2);
		ft_lstclear(words);
		return (0);
	}
	return (1);
}

void	open_files(t_joins **stack_2)
{
	t_joins *tmp = *stack_2;
	int		i;

	while(tmp)
	{
		i = 0;
		while(tmp->content[i])
		{
			if(ft_strcmp(tmp->content[i], ">") == 0)
			{
				if (tmp->out > 1)
					close(tmp->out);
				tmp->out = open(tmp->content[++i], O_CREAT | O_TRUNC | O_WRONLY, 0777);
			}
			else if(ft_strcmp(tmp->content[i], "<") == 0)
			{
				if (tmp->in > 0)
					close(tmp->in);
				tmp->in = open(tmp->content[++i], O_RDONLY, 0777);
			}
			else if(ft_strcmp(tmp->content[i], ">>") == 0)
			{
				if (tmp->out > 1)
					close(tmp->out);
				tmp->out = open(tmp->content[++i], O_CREAT | O_RDWR | O_APPEND, 0777);
			}
			i++;
		}
		tmp = tmp->next;
	}
}


int	ft_check_content(char **dst , int *i)
{
	int	j;

	*i = 0;
	j = 0;
	while (dst[*i])
	{
		if (ft_strcmp(dst[*i], ">") == 0 || ft_strcmp(dst[*i], "<") == 0 || ft_strcmp(dst[*i], ">>") == 0)
			j++;
		(*i)++;
	}
	return (j);
}



char	**ft_create_exe_dst(char **ptr)
{
	char	**dst;
	int		i;
	int		j;
	int		x;

	j = ft_check_content(ptr, &i);
	if (i > 0)
	{
		i = i - (j * 2);
		dst = (char **)malloc(sizeof(char *) * (i + 1));
		if (!dst)
			return (ptr);
		j = 0;
		x = 0;
		while (j < i)
		{
			if (ft_strcmp(ptr[x], ">") == 0 || ft_strcmp(ptr[x], "<") == 0 || ft_strcmp(ptr[x], ">>") == 0)
				x += 2;
			dst[j++] = ft_strdup(ptr[x++]);
		}
		dst[j] = NULL;
		free_split(ptr);
		return (dst);
	}
	else	
		return (ptr);

}

t_joins	*ft_parse_stack(t_words **words, t_env **env)
{
	t_joins	*stack_2;
	t_joins	*new;
	t_joins	*tmp;
	t_words *head;
	int		i;

	stack_2 = ft_lstnew_joins(words);
	stack_2->content = ft_create_list(stack_2, *words, env);
	if (!ft_syntax_error(stack_2, words))
		return (stack_2);
	head = (*words);
	while (head)
	{
		if (head->type == PIPE)
		{
			head = head->next;
			new = ft_lstnew_joins(words);
			new->content = ft_create_list(new, head, env);
			if (new && !new->content)
				return (stack_2);
			ft_lstaddback_joins(&stack_2, new);
			if (!ft_syntax_error(new, words))
				return (stack_2);
		}
		else
			head = head->next;
	}
	open_files(&stack_2);
	tmp = stack_2;
	while (tmp)
	{
		tmp->content = ft_create_exe_dst(tmp->content);
		tmp = tmp->next;
	}

	tmp = stack_2;
	while (tmp)
	{
		if (tmp->in == -5)
			return (ft_lstclear(words), stack_2);
		tmp = tmp->next;
	}
	tmp = stack_2;
	head = (*words);
	while(tmp)
	{
		if (tmp->in == -1  || tmp->out == -1)
		{
			while (head && head->type == WORD)
				head = head->next;
			if ( head && head->next)
				head = head->next;
			ft_putstr("Minishell$: ", 2);
			ft_putstr(head->word, 2);
			ft_putstr(" No such file or directory\n", 2);
			while (head && head->type != PIPE)
				head = head->next;
		}
		while (head && head->type != PIPE)
			head = head->next;
		if (head && head->next)
			head = head->next;
		tmp = tmp->next;
	}
	ft_lstclear(words);
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
