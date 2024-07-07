#include "../minishell.h"

int	ft_check_content(char **dst, int *i)
{
	int	j;

	*i = 0;
	j = 0;
	while (dst[*i])
	{
		if (ft_strcmp(dst[*i], ">") == 0 || ft_strcmp(dst[*i], "<") == 0
			|| ft_strcmp(dst[*i], ">>") == 0)
			j++;
		(*i)++;
	}
	return (j);
}

int	ft_count_word_if_no_content(t_joins *tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tmp->content[i])
	{
		if (tmp->content && ft_strlen(tmp->content[i]) == 0 && !tmp->quotes)
			j++;
		i++;
	}
	return (j);
}

void	ft_check_redi(char *ptr, int *x)
{
	if (ft_strcmp(ptr, ">") == 0 || ft_strcmp(ptr, "<") == 0
		|| ft_strcmp(ptr, ">>") == 0)
		*x += 2;
}

char	**ft_create_exe_dst(char **ptr, t_joins *tmp)
{
	char	**dst;
	int		i;
	int		j;
	int		x;

	j = ft_check_content(ptr, &i);
	if (i > 0)
	{
		i = (i - (j * 2)) - ft_count_word_if_no_content(tmp);
		dst = (char **)malloc(sizeof (char *) * (i + 1));
		if (!dst)
			return (ptr);
		((1) && (j = 0, x = 0));
		while (j < i)
		{
			ft_check_redi(ptr[x], &x);
			if (tmp->content && ft_strlen(tmp->content[x]) == 0 && !tmp->quotes)
				x++;
			else
				dst[j++] = ft_strdup(ptr[x++]);
		}
		return (dst[j] = NULL, free_split(ptr), dst);
	}
	else
		return (ptr);
}

int	delete_check_error(t_words **words, t_joins *stack_2)
{
	t_joins	*tmp;

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
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
