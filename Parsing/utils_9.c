#include "../minishell.h"

void	ft_creat_list_no_herd(t_words *head, char **dst, int *i)
{
	char	**str;
	int		j;

	j = 0;
	if (head->is == 1)
	{
		dst[(*i)++] = ft_strdup(head->word);
		head = head->next;
		return ;
	}
	multiple(&head->word, 0);
	str = ft_split(head->word, ' ');
	if (!str)
		return ;
	while (str[j])
	{
		multiple(&str[j], 0);
		dst[(*i)++] = ft_strdup(str[j++]);
	}
	multiple(&head->word, 0);
	free_split(str);
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

char	**ft_create_list(t_joins *stack_2, t_words *head, t_env **env)
{
	char	**dst;
	int		words;

	words = ft_words(head);
	dst = (char **)malloc(sizeof (char *) * (words + 1));
	if (!dst)
		return (NULL);
	dst = ft_create_l_all(head, stack_2, env, dst);
	return (dst);
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
