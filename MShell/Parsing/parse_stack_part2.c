#include "../minishell.h"

static void	ft_herd_sig(int i)
{
	(void)i;
	if (i == SIGINT)
		close(STDIN_FILENO);
}

void	ft_close_io(t_joins *stack_2)
{
	if (stack_2->out > 2)
		close(stack_2->out);
	if (stack_2->in > 2)
		close(stack_2->in);
}

static void	ft_handle_herd(t_joins *stack_2, t_words *head, t_env **env)
{
	char	*file;
	int		i;
	char	*nb;

	((1) && (i = 0, file = ft_strdup("/tmp/.herd_file")));
	while (access(file, F_OK) == 0)
	{
		free(file);
		nb = ft_itoa(i++);
		file = ft_strjoin("/tmp/.herd_file", nb);
		free(nb);
	}
	head = head->next;
	ft_close_io(stack_2);
	stack_2->out = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	signal(SIGINT, ft_herd_sig);
	rl_catch_signals = 0;
	if (ft_herd_while(stack_2, head, env) == -1)
	{
		ft_unlink_free(file);
		return ;
	}
	((1) && close(stack_2->out), stack_2->out = 1);
	stack_2->in = open(file, O_CREAT | O_RDONLY, 0777);
	ft_unlink_free(file);
}

void	ft_creat_list_nop(t_words *head, char **dst, int *i)
{
	if (head->type != 6)
		dst[(*i)++] = ft_strdup(head->word);
	else if (head->type == 6 && head->word[0] != '\0')
		ft_creat_list_no_herd(head, dst, i);
	else if (head->type == 6 && head->word[0] == '\0')
		dst[(*i)++] = ft_strdup(head->word);
}

char	**ft_create_l_all(t_words *head, t_joins *s2, t_env **env, char **dst)
{
	int		i;
	int		words;

	i = 0;
	words = ft_words(head);
	while (head && head->type != PIPE && hundle_error(head) != 0)
	{
		if (i <= words)
		{
			if (head->type == HERD)
			{
				ft_handle_herd(s2, head, env);
				if (s2->in == -5)
					return (ft_exit_status(env, "1"), dst[i] = NULL, dst);
				head = head->next;
			}
			else
				ft_creat_list_nop(head, dst, &i);
		}
		if (head)
			head = head->next;
	}
	return (dst[i] = NULL, dst);
}
