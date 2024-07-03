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

int	ft_words(t_words *head)
{
	int	i;

	i = 0;
	while (head && hundle_error(head) != 0)
	{
		if (head->type == PIPE)
			return (i);
		if (head->type == HERD)
		{
			if (head)
				head = head->next;
			if (head)
				head = head->next;
			continue ;
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
		if (head)
			head = head->next;
	}
	return (i);
}

char	**ft_create_list(t_joins *stack_2, t_words *head, t_env **env)
{
	char	**dst;
	int		words;
	int		i;
	char	**str;
	int		j;

	words = ft_words(head);
	dst = (char **)malloc(sizeof (char *) * (words + 1));
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
				if (stack_2->in == -5)
				{
					ft_exit_status(env, "1");
					return (dst[i] = NULL, dst);
				}
				head = head->next;
			}
			else
			{
				if (head->type != 6)
					dst[i++] = ft_strdup(head->word);
				else if (head->type == 6 && head->word[0] != '\0')
				{
					if (head->is == 1)
					{
						dst[i++] = ft_strdup(head->word);
						head = head->next;
						continue ;
					}
					multiple(&head->word, 0);
					str = ft_split(head->word, ' ');
					if (!str)
						return (NULL);
					j = 0;
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
		if (head)
			head = head->next;
	}
	return (dst[i] = NULL, dst);
}

void	open_files(t_joins **stack_2, t_words *words, t_env *env_stack)
{
	t_joins	*tmp;
	int		i;

	tmp = (*stack_2);
	while (tmp)
	{
		i = 0;
		if (hundle_error(words) == 10)
		{
			printf ("Minishell : ambiguous redirect\n");
			ft_exit_status(&env_stack, "1");
			free_split(tmp->content);
			tmp->content = NULL;
		}
		else
		{
			while (tmp->content[i])
			{
				if (hundle_error(words) == 10)
				{
					printf ("Minishell : ambiguous redirect\n");
					ft_exit_status(&env_stack, "1");
					free_split(tmp->content);
					tmp->content = NULL;
					break ;
				}
				if (ft_strcmp(tmp->content[i], ">") == 0)
				{
					if (tmp->out > 1)
						close(tmp->out);
					tmp->out = open(tmp->content[++i], O_CREAT
							| O_TRUNC | O_WRONLY, 0644);
					if (words)
						words = words->next;
				}
				else if (ft_strcmp(tmp->content[i], "<") == 0)
				{
					if (tmp->in > 0)
						close(tmp->in);
					tmp->in = open(tmp->content[++i], O_RDONLY, 0644);
					if (words)
						words = words->next;
				}
				else if (ft_strcmp(tmp->content[i], ">>") == 0)
				{
					if (tmp->out > 1)
						close(tmp->out);
					tmp->out = open(tmp->content[++i], O_CREAT
							| O_RDWR | O_APPEND, 0644);
					if (words)
						words = words->next;
				}
				if (!tmp->error && (tmp->in == -1 || tmp->out == -1))
				{
					ft_putstr("Minishell$: ", 2);
					ft_putstr(tmp->content[i], 2);
					ft_putstr(" No such file or directory\n", 2);
					ft_exit_status(&env_stack, "1");
					free_split(tmp->content);
					tmp->content = NULL;
					break ;
				}
				if (words)
					words = words->next;
				i++;
			}
		}
		while (words && words->type != PIPE)
			words = words->next;
		if (words)
			words = words->next;
		if (tmp)
			tmp = tmp->next;
	}
}

int	ft_check_for_syntax(t_words *head, t_env *env)
{
	if (ft_strcmp(head->word, "|") == 0)
	{
		printf ("Minishell : syntax error near unexpected token\n");
		ft_exit_status(&env, "258");
		return (1);
	}
	while (head)
	{
		if (hundle_error(head) == 0)
		{
			printf ("Minishell : syntax error near unexpected token\n");
			ft_exit_status(&env, "258");
			return (1);
		}
		head = head->next;
	}
	return (0);
}

int	strlen_no_quotes(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				res++;
				i++;
			}
		}
		else if (str[i] == '\'')
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
		if (str[i])
			i++;
	}
	return (res);
}

char	*dele_quotes(char **str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	res = NULL;
	res = malloc(strlen_no_quotes((*str)) + 1);
	if (res == NULL)
		return (NULL);
	while ((*str)[i])
	{
		if ((*str)[i] == '\"')
		{
			i++;
			while ((*str)[i] && (*str)[i] != '\"')
			{
				res[j] = (*str)[i];
				i++;
				j++;
			}
		}
		else if ((*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] && (*str)[i] != '\'')
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
	t_joins	*tmp;
	int		i;

	(void)c;
	if (!stack_2)
		return ;
	tmp = (*stack_2);
	while (tmp)
	{
		i = 0;
		while (tmp->content[i])
		{
			if (check_double_qout(tmp->content[i]))
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
	t_words	*head;
	int		syntax;

	if (!words || !env)
		return (NULL);
	head = (*words);
	syntax = ft_check_for_syntax(*words, *env);
	stack_2 = ft_lstnew_joins(words);
	stack_2->content = ft_create_list(stack_2, *words, env);
	if (hundle_error(head) == 0 || stack_2->in == -5)
		return (ft_lstclear(words), stack_2);
	while (head)
	{
		if (head->type == PIPE)
		{
			head = head->next;
			new = ft_lstnew_joins(words);
			new->content = ft_create_list(new, head, env);
			ft_lstaddback_joins(&stack_2, new);
			if (hundle_error(head) == 0 || new->in == -5)
				return (ft_lstclear(words), stack_2);
			if (new && !new->content)
				return (stack_2);
		}
		else
			head = head->next;
	}
	if (syntax == 1)
		return (ft_lstclear(words), stack_2);
	delete_qoutes_1(&stack_2, '\"');
	open_files(&stack_2, *words, *env);
	tmp = stack_2;
	while (tmp)
	{
		if (tmp->content)
			tmp->content = ft_create_exe_dst(tmp->content, tmp);
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
		if (tmp->content != NULL)
			ft_run_commad(&stack_2, env, tmp->content[0]);
	}
	else
		ft_is_pipe(&stack_2, env);
	return (stack_2);
}
