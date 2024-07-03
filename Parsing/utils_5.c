#include "../minishell.h"

int	ft_get_env_len(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

t_env	*ft_lstnew_env(char *val_1, char *val_2)
{
	t_env	*head;
	char	*t;

	t = val_2;
	head = (t_env *)malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	if (!t)
		head->equal = 0;
	else if (*t == '=')
	{
		t++;
		head->equal = 1;
	}
	else
		head->equal = 0;
	head->is = 0;
	head->key = ft_strdup(val_1);
	if (ft_strcmp(val_1, "_") == 0)
		head->value = ft_strdup("/usr/bin/env");
	else
		head->value = ft_strdup(t);
	head->print = 1;
	head->next = NULL;
	return (head);
}

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

char	**ft_create_exe_dst(char **ptr, t_joins *tmp)
{
	char	**dst;
	int		i;
	int		j;
	int		x;
	int		k;

	j = ft_check_content(ptr, &i);
	k = ft_count_word_if_no_content(tmp);
	if (i > 0)
	{
		i = i - (j * 2);
		i -= k;
		dst = (char **)malloc(sizeof (char *) * (i + 1));
		if (!dst)
			return (ptr);
		j = 0;
		x = 0;
		while (j < i)
		{
			if (ft_strcmp(ptr[x], ">") == 0 || ft_strcmp(ptr[x], "<") == 0
				|| ft_strcmp(ptr[x], ">>") == 0)
				x += 2;
			if (tmp->content && ft_strlen(tmp->content[x]) == 0 && !tmp->quotes)
				x++;
			else
				dst[j++] = ft_strdup(ptr[x++]);
		}
		dst[j] = NULL;
		free_split(ptr);
		return (dst);
	}
	else
		return (ptr);
}
