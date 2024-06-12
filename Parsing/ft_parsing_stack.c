#include "../minishell.h"

int	ft_strlen_space(t_words *words)
{
	char	**dst;
	int		i;

	i = 0;
	multiple(&words->word, 0);
	dst = ft_split(words->word, ' ');
	if (!dst)
		return (0);
	while (dst[i])
		i++;
	free_split(dst);
	multiple(&words->word, 0);
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
	
	while (head && hundle_error(head) != 0)
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
		if (head->type == 6 && head->word[0] != '\0')
		{
			if (head->is == 1)
				i++;
			else
				i += ft_strlen_space(head);
		}
		else if (head->type == 6 && head->word[0] == '\0' && head->is)
			i++;
		else 
			i++;
		if(head)
			head = head->next;
	}
	return (i);
}

int	ft_check_ctr_herd(t_joins *head, t_words **words, int is)
{
	t_joins *tmp = head;
	while (tmp)
	{
		if (tmp->in == -5 || tmp->error)
		{
			if (is)
				ft_lstclear(words);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	**ft_create_list(t_joins *stack_2, t_words *head, t_env **env)
{
	char	**dst;
	int		words;
	int		i;
	static int in;

	words = ft_words(head);
	// printf("[%d]\n", words);
	dst = (char **)malloc(sizeof(char *) * (words + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (head && head->type != PIPE && hundle_error(head) != 0)
	{
		if (i <= words)
		{
			if (head->type == HERD)
			{
				ft_handle_herd(stack_2, head, env);
				in = stack_2->in;
				if(stack_2->in == -5)
					return (dst[i] = NULL, dst);
				head = head->next;
			}
			else
			{
				if(head->type != 6)
					dst[i++] = ft_strdup(head->word);
				else if (head->type == 6 && head->word[0] != '\0')
				{
					char **str;
					if (head->is == 1)
					{
						dst[i++] = ft_strdup(head->word);
						head = head->next;
						continue;
					}
					
					multiple(&head->word, 0);
					str = ft_split(head->word, ' ');
					if (!str)
						return (NULL);
					int j = 0;
					while (str[j])
					{
						multiple(&str[j], 0);
						dst[i++] = ft_strdup(str[j++]);
					}
					multiple(&head->word, 0);
					free_split(str);
				}
				else if (head->type == 6 && head->word[0] == '\0')
					dst[i++] = ft_strdup(head->word);
			}
		}
		if(head)
			head = head->next;
	}
	return (dst[i] = NULL, dst);
}

// int	ft_syntax_error(t_joins *head, t_joins *node, t_words **words)
// {
// 	if (!node->content[0] && (node->in == 0 && node->out == 1) && !node->error)
// 	{
// 		if (ft_check_ctr_herd(head, words, 1))
// 			return (0);
// 		ft_putstr("Minishell$ :syntax error near unexpected token\n", 2);
// 		ft_lstclear(words);
// 		return (0);
// 	}
// 	return (1);
// }


// if (hundle_error(head) == 10)
// {
// 	if (in != -5)
// 	{
// 		printf("Minishell : ambiguous redirect\n");
// 		stack_2->error = 1;
// 	}
// 	break ;
// }

void	open_files(t_joins **stack_2, t_words *words, t_env *env_stack)
{
	t_joins *tmp = *stack_2;
	int		i;

	while(tmp)
	{
		i = 0;
		if (hundle_error(words) == 10)
		{
			printf("Minishell : ambiguous redirect\n");
			ft_exit_status(&env_stack, "1");
			free_split(tmp->content);
			tmp->content = NULL;
		}
		else
		{
			while(tmp->content[i])
			{
				if (hundle_error(words) == 10)
				{
					printf("Minishell : ambiguous redirect\n");
					ft_exit_status(&env_stack, "1");
					free_split(tmp->content);
					tmp->content = NULL;
					break;
				}
				if(ft_strcmp(tmp->content[i], ">") == 0)
				{
					if (tmp->out > 1)
						close(tmp->out);
					tmp->out = open(tmp->content[++i], O_CREAT | O_TRUNC | O_WRONLY, 0777);
					if(words)
						words = words->next;
				}
				else if(ft_strcmp(tmp->content[i], "<") == 0)
				{
					if (tmp->in > 0)
						close(tmp->in);
					tmp->in = open(tmp->content[++i], O_RDONLY, 0777);
					if(words)
						words = words->next;
				}
				else if(ft_strcmp(tmp->content[i], ">>") == 0)
				{
					if (tmp->out > 1)
						close(tmp->out);
					tmp->out = open(tmp->content[++i], O_CREAT | O_RDWR | O_APPEND, 0777);
					if(words)
						words = words->next;
				}
				if (!tmp->error && (tmp->in == -1 || tmp->out == -1))
				{
					ft_putstr("Minishell$: ", 2);
					ft_putstr(tmp->content[i], 2);
					ft_putstr(" No such file or directory\n", 2);
					ft_exit_status(&env_stack, "1");
					break ;
				}
				if(words)
					words = words->next;
				i++;
			}
		}
		while(words && words->type != PIPE)
				words = words->next;
		if(words)
			words = words->next;
		if(tmp)
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

int	ft_check_for_syntax(t_words *head, int *herd, t_env *env)
{
	int	i;

	i = 0;
	(*herd) = 0;
	while (head)
	{
		if (head->type == HERD)
			(*herd)++;
		if (hundle_error(head) == 0)
		{
			printf("Minishell : syntax error near unexpected token\n");
			ft_exit_status(&env, "258");
			return (1);
		}
		head = head->next;
	}
	return (0);
}

int	strlen_no_quotes(char *str)
{
	int i = 0;
	int res = 0;
	while (str[i])
	{
		if(str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				res++;
				i++;
			}
		}
		else if(str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				res++;
				i++;
			}
		}
		else
			res++;
		if(str[i])
			i++;
	}
	return (res);
}

char	*dele_quotes(char **str)
{
	int i = 0;
	int j = 0;
	char	*res = NULL;
	res = malloc(strlen_no_quotes((*str)) + 1);
	if(res == NULL)
		return (NULL);
	while((*str)[i])
	{
		if((*str)[i] == '\"')
		{
			i++;
			while((*str)[i]  && (*str)[i] != '\"')
			{
				res[j] = (*str)[i];
				i++;
				j++;
			}

		}
		else if((*str)[i] == '\'')
		{
			i++;
			while((*str)[i]  && (*str)[i] != '\'')
			{
				res[j] = (*str)[i];
				i++;
				j++;
			}

		}
		else
		{
			res[j] = (*str)[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	free((*str));
	return (res);
}
void	delete_qoutes_1(t_joins	**stack_2, char c)
{
	t_joins *tmp = *stack_2;
	(void)c;
	while(tmp)
	{
		int i = 0;
		while(tmp->content[i])
		{
			if(check_double_qout(tmp->content[i]))
			{
				tmp->content[i] = dele_quotes(&tmp->content[i]);
				tmp->quotes = 1;
			}
			i++;
		}		
		tmp = tmp->next;
	}
}

t_joins	*ft_parse_stack(t_words **words, t_env **env)
{
	t_joins	*stack_2;
	t_joins	*new;
	t_joins	*tmp;
	t_words *head;
	int		i;
	int		syntax;
	int		num_herd;

	head = (*words);
	syntax = ft_check_for_syntax(*words, &num_herd, *env);
	stack_2 = ft_lstnew_joins(words);
	stack_2->content = ft_create_list(stack_2, *words, env);
	if (hundle_error(head) == 0)
		return (ft_lstclear(words), stack_2);
	while (head)
	{
		if (head->type == PIPE)
		{
			head = head->next;
			new = ft_lstnew_joins(words);
			new->content = ft_create_list(new, head, env);
			ft_lstaddback_joins(&stack_2, new);
			if (hundle_error(head) == 0)
				return (ft_lstclear(words), stack_2);
			if (new && !new->content)
				return (stack_2);
		}
		else
			head = head->next;
	}
	if (ft_check_ctr_herd(stack_2, words, 1))
		return (ft_lstclear(words), stack_2);
	if(syntax == 1)
		return (ft_lstclear(words), stack_2);
	delete_qoutes_1(&stack_2, '\"');
	open_files(&stack_2, *words, *env);
	tmp = stack_2;
	while (tmp)
	{
		if (tmp->content)
			tmp->content = ft_create_exe_dst(tmp->content);
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
		//bad if
		if (tmp->content == NULL && tmp->in == 0 && tmp->out == 1)
			return (stack_2);
		if (tmp->in < 0 || tmp->out < 0)
			return (stack_2);
		ft_run_commad(&stack_2, env, tmp->content[0]);
	}
	else
		ft_is_pipe(&stack_2, env);
	return (stack_2);
}
