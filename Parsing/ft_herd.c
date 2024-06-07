#include "../minishell.h"

int	g_herd;

void	ft_herd_sig(int i)
{
	(void)i;
	if (i == SIGINT)
	{
		close(STDIN_FILENO);
		g_herd = 1;
	}
}

void	based_on_trim(char **str)
{
	if (*str[0] == '\"')
		*str = ft_strtrim(*str, "\"");
	else if (*str[0] == '\'')
		*str= ft_strtrim(*str, "\'");
}

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_check_word_type(t_joins *stack_2, t_words **head, int *i, char **dst)
{
	// printf("[%s] [%d]\n",(*head)->word, (*head)->type);
	if ((*head)->type == WORD)
	{
		dst[(*i)++] = ft_strdup((*head)->word);
		// printf("%s\n", (*head)->word);
		// if ((*head)->word[0] == '$' && (ft_strcmp((*head)->word, "export") != 0 || ft_strcmp((*head)->word, "awk") == 0) && (*head)->next && (*head)->next->type == 0)
		// {
		// 	puts("---");
		// 	(*head)->next->type = 6;
		// }	
	}
	else if ((*head)->type == 6 && (*head)->word[0] != '\0')
	{
		if((*head)->is == 1)
		{
			dst[(*i)++] = ft_strdup((*head)->word);
			return ;
		}
		char	**str;
		str = ft_split((*head)->word, ' ');
		if (!str)
			return ;
		int j = 0;
		while (str[j])
			dst[(*i)++] = ft_strdup(str[j++]);
		free_split(str);
	}
	else if ((*head)->type == REDOU)
	{
		ft_next_node(head);
		if (ft_strlen((*head)->word) == 2 && (*head)->is == 1)
		{
			stack_2->out = -1;
			return ;
		}
		based_on_trim(&(*head)->word);
		stack_2->out = open((*head)->word, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	}
	else if ((*head)->type == REDIN)
	{
		ft_next_node(head);
		if (ft_strlen((*head)->word) == 2 && (*head)->is == 1)
		{
			stack_2->in = -1;
			return ;
		}
		based_on_trim(&(*head)->word);
		stack_2->in = open((*head)->word, O_RDONLY, 0777);
	}
	else if ((*head)->type == APPEND)
	{
		ft_next_node(head);
		if (ft_strlen((*head)->word) == 2 && (*head)->is == 1)
		{
			stack_2->out = -1;
			return ;
		}
		based_on_trim(&(*head)->word);
		stack_2->out = open((*head)->word, O_CREAT | O_RDWR | O_APPEND, 0777);
	}
	else if ((*head)->type == 7)
		ft_next_node(head);
}

char	*ft_env_eq(t_env **env, char *key)
{
	t_env	*head;

	head = (*env);
	if (*key && key[0] == '$')
	{
		while (head)
		{
			if (ft_strcmp(head->key, key + 1) == 0)
				return (head->value);
			head = head->next;
		}
	}
	return (key);
}

void	ft_print_free(char *str, int fd)
{
	int	j;

	j = -1;
	while (str[++j])
		write(fd, &str[j], 1);
	free(str);
	write(fd, "\n", 1);
}

int	ft_herd_while_2(t_joins *stack_2, t_words **head, t_env **env, char *str)
{
	char	*tmp;
	int		is;

	is = 0;
	if ((*head)->is && ft_strlen((*head)->word) > 2)
	{
		tmp = all_expand((*head)->word, *env, 1);
		is = 1;
	}
	if (!str 
			|| (ft_strcmp(tmp, str) == 0
			|| ft_strcmp((*head)->word, str) == 0
			|| ft_strcmp("\"\"", str) == 0
			|| ft_strcmp("\'\'", str) == 0)
		|| (!str[0] && (*head)->is && ft_strlen(tmp) == 2))
	{
		if (is)
			free(tmp);
		free(str);
		return (1);
	}
	if (!str)
	{
		free(str);
		write(stack_2->out, "\n", 1);
		return (2);
	}
	if (!(*head)->is)
	{
		tmp = all_expand(str, *env, 0);
		free(str);
		ft_print_free(tmp, stack_2->out);
	}
	else
	{
		free(tmp);
		ft_print_free(str, stack_2->out);
	}
	return (0);
}

void	ft_herd_while(t_joins *stack_2, t_words **head, t_env **env)
{
	char	*str;
	int		out;

	while (1)
	{
		str = readline("> ");
		if (g_herd)
		{
			dup2(STDIN_FILENO, open(ttyname(1), O_RDONLY, 0777));
			free(str);
			g_herd = 0;
		}
		out = ft_herd_while_2(stack_2, head, env, str);
		if (out == 1)
			break ;
		else if (out == 2)
			break ;
	}
}

static int	ft_num_len(long num)
{
	int		i;

	i = 0;
	if (num <= 0)
		num *= -1;
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		n_len;
	char	*str;
	long	num;

	num = n;
	n_len = ft_num_len(num);
	str = (char *)malloc((n_len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[n_len--] = '\0';
	if (num == 0)
		str[0] = '0';
	if (num < 0)
		num *= -1;
	while (num > 0 && n_len >= 0)
	{
		str[n_len] = '0' + (num % 10);
		num /= 10;
		n_len--;
	}
	return (str);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_handle_herd(t_joins *stack_2, t_words **head, t_env **env)
{
	char	*file = ft_strjoin("../.herd_file", ft_itoa((int)get_current_time()));

	ft_next_node(head);
	stack_2->out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	signal(SIGINT, ft_herd_sig);
	rl_catch_signals = 0;
	ft_herd_while(stack_2, head, env);
	close(stack_2->out);
	stack_2->out = 1;
	stack_2->in = open(file, O_CREAT | O_RDONLY, 0777);
}

void	ft_next_node(t_words **head)
{
	t_words	*tmp;

	if (!(*head)->next)
		tmp = NULL;
	else
		tmp = (*head)->next;
	free((*head)->word);
	free((*head));
	(*head) = tmp;
}
