#include "../minishell.h"

static int	ft_add(t_words **head, char *str, t_env *env_stack)
{
	t_words	*node;

	multiple(&str, 0);
	if (str[0] == '<' && str[0 + 1] == '<')
		return (1);
	node = ft_lstnew(str, env_stack);
	if (node->word[0] == '\0')
	{
		ft_lstdelone(node);
		return (0);
	}
	ft_lstadd_back(head, node);
	return (0);
}

void	free_split(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
}

t_words	*ft_lstnew_herd(char *val_1)
{
	t_words	*head;

	head = (t_words *)malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	head->type = 0;
	if ((val_1[0] == '\'' || val_1[0] == '\"')
		&& (val_1[ft_strlen(val_1) - 1] == '\''
			|| val_1[ft_strlen(val_1) - 1] == '\"'))
		head->is = 1;
	else
		head->is = 0;
	head->word = ft_strdup(val_1);
	head->next = NULL;
	return (head);
}

void	add_struct(char *str, t_words **words, t_env *env_stack)
{
	char	**tmp;
	int		j;
	t_words	*node;

	j = 0;
	multiple(&str, 0);
	tmp = ft_split(str, ' ');
	if (tmp == NULL || *tmp == NULL)
		return ;
	while (tmp[j])
	{
		if (ft_add(words, tmp[j], env_stack))
		{
			node = ft_lstnew(tmp[j], env_stack);
			ft_lstadd_back(words, node);
			j++;
			if (tmp[j])
			{
				node = ft_lstnew_herd(tmp[j]);
				ft_lstadd_back(words, node);
			}
			else
				j--;
		}
			j++;
	}
	free_split(tmp);
}
