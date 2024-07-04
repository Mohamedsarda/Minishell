#include "../minishell.h"

void	ft_words_her(int *i, t_words *head)
{
	if (head->is == 1)
		(*i)++;
	else
		*i += ft_strlen_space(head);
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
			ft_words_her(&i, head);
		else if (head->type == 6 && head->word[0] == '\0' && head->is)
			i++;
		else
			i++;
		if (head)
			head = head->next;
	}
	return (i);
}
