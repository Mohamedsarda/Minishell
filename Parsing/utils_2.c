#include "../minishell.h"


void	ft_herd_sig(int i)
{
	(void)i;
	if (i == SIGINT)
		close(STDIN_FILENO);
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

void	ft_unlink_free(char *str)
{
	unlink(str);
	signal(SIGINT, ft_sighandler);
	free(str);
}

void	ft_handle_herd(t_joins *stack_2, t_words *head, t_env **env)
{
	char	*file;
	int		i;

	file = ft_strdup("../.herd_file");
	i = 0;
	while (access(file, F_OK) == 0)
	{
		free(file);
		file = ft_strjoin("../.herd_file", ft_itoa(i++));
	}
	head = head->next;
	stack_2->out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	signal(SIGINT, ft_herd_sig);
	rl_catch_signals = 0;
	if (ft_herd_while(stack_2, head, env) == -1)
	{
		ft_unlink_free(file);
		return ;
	}
	close(stack_2->out);
	stack_2->out = 1;
	stack_2->in = open(file, O_CREAT | O_RDONLY, 0777);
	ft_unlink_free(file);
}

int	ft_herd_while(t_joins *stack_2, t_words *head, t_env **env)
{
	char	*str;
	int		out;

	while (1)
	{
		str = readline("> ");
		if (!isatty(STDIN_FILENO))
		{
			dup2(STDIN_FILENO, open(ttyname(1), O_RDONLY, 0777));
			free(str);
			stack_2->in = -5;
			return (-1);
		}
		out = ft_herd_while_2(stack_2, head, env, str);
		if (out == 1)
			break ;
		else if (out == 2)
			break ;
	}
	return (0);
}

