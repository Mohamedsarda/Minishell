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

void	ft_check_word_type(t_joins *stack_2, t_words **head, int *i, char **dst)
{
	if ((*head)->type == WORD || (*head)->type == ENVV)
		dst[(*i)++] = ft_strdup((*head)->word);
	else if ((*head)->type == REDOU)
	{
		ft_next_node(head);
		stack_2->out = open((*head)->word, O_CREAT | O_TRUNC | O_WRONLY, 0777);
	}
	else if ((*head)->type == REDIN)
	{
		ft_next_node(head);
		stack_2->in = open((*head)->word, O_RDONLY, 0777);
	}
	else if ((*head)->type == APPEND)
	{
		ft_next_node(head);
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

void	ft_herd_while(t_joins *stack_2, t_words **head, t_env **env)
{
	char	*str;
	char	*tmp;

	while (1)
	{
		str = readline("> ");
		if (g_herd)
		{
			dup2(STDIN_FILENO, open(ttyname(1), O_RDONLY, 0777));
			free(str);
			g_herd = 0;
		}
		if (!str || ft_strcmp((*head)->word, str) == 0 || ft_strcmp("", str) == 0)
		{
			free(str);
			break ;
		}
		if (!str[0])
		{
			free(str);
			continue ;
		}
		if (!(*head)->is)
		{
			tmp = ft_strdup(ft_env_eq(env, str));
			free(str);
			ft_print_free(tmp, stack_2->out);
		}
		else
			ft_print_free(str, stack_2->out);

		}
}

void	ft_handle_herd(t_joins *stack_2, t_words **head, t_env **env)
{
	ft_next_node(head);
	stack_2->out = open(".herd_file", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	signal(SIGINT, ft_herd_sig);
	rl_catch_signals = 0;
	ft_herd_while(stack_2, head, env);
	close(stack_2->out);
	stack_2->out = 1;
	stack_2->in = open(".herd_file", O_CREAT | O_RDONLY, 0777);
}

void	ft_next_node(t_words **head)
{
	t_words	*tmp;

	tmp = (*head)->next;
	free((*head)->word);
	free((*head));
	(*head) = tmp;
}
