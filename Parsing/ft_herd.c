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
	if ((*head)->type == WORD)
		dst[(*i)++] = ft_strdup((*head)->word);
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
		stack_2->out = open((*head)->word, O_CREAT | O_RDWR | O_APPEND, 0777);
	}
	else if ((*head)->type == HERD)
		ft_handle_herd(stack_2, head);
	else if ((*head)->type == 7)
		ft_next_node(head);
}

void	ft_herd_while(t_joins *stack_2, t_words **head)
{
	char	*str;
	int		j;

	while (1)
	{
		str = readline("> ");
		if (g_herd)
		{
			dup2(STDIN_FILENO, open(ttyname(1), O_RDONLY, 0777));
			free(str);
			g_herd = 0;
		}
		if (!str || ft_strcmp((*head)->word, str) == 0)
			break ;
		if (!str[0])
		{
			free(str);
			continue ;
		}
		j = -1;
		while (str[++j])
			write(stack_2->out, &str[j], 1);
		free(str);
		write(stack_2->out, "\n", 1);
	}
}

void	ft_handle_herd(t_joins *stack_2, t_words **head)
{
	ft_next_node(head);
	stack_2->out = open(".herd_file", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	signal(SIGINT, ft_herd_sig);
	rl_catch_signals = 0;
	ft_herd_while(stack_2, head);
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
