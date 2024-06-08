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

void	ft_handle_herd(t_joins *stack_2, t_words **head, t_env **env)
{
	char	*file;
	int		i;

	file = ft_strdup("../.herd_file");
	i = 0;
	while (access(file, F_OK) == 0)
		file = ft_strjoin("../.herd_file", ft_itoa(i++));
	ft_next_node(head);
	stack_2->out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	signal(SIGINT, ft_herd_sig);
	rl_catch_signals = 0;
	ft_herd_while(stack_2, head, env);
	close(stack_2->out);
	stack_2->out = 1;
	stack_2->in = open(file, O_CREAT | O_RDONLY, 0777);
	unlink(file);
	free(file);
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

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
