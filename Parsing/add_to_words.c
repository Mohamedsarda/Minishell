#include "../minishell.h"

static void	ft_add(t_words **head, char *a, t_env *env_stack)
{
	t_words	*node;

	node = ft_lstnew(a, env_stack);
	ft_lstadd_back(head, node);
}

void	free_split(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
}

void	add_struct(char *str, t_words **words, t_env *env_stack)
{
	char	**tmp;
	int		j;

	j = -1;
	tmp = ft_split(str, ' ');
	if (tmp == NULL || *tmp == NULL)
		return ;
	while (tmp[++j])
		ft_add(words, tmp[j], env_stack);
	free_split(tmp);
}
