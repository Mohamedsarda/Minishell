#include "../minishell.h"

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