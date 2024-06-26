#include "../minishell.h"

char	*ft_env_eq(t_env **env, char *key)
{
	t_env	*head;

	head = (*env);
	if (*key && key[0] == '$')
	{
		while (head)
		{
			if (ft_strcmp(head->key, key + 1) == 0)
				return (head->value);
			head = head->next;
		}
	}
	return (key);
}

char	*ft_remove_qoutes_herd(char *str)
{
	char	*dst;
	int		i;
	int		j;

	i = 1;
	j = 0;
	dst = malloc(ft_strlen(str) - 1);
	if (!dst)
		return (NULL);
	while (str && str[i] && str[i + 1] != '\0')
		dst[j++] = str[i++];
	dst[j] = '\0';
	free(str);
	return (dst);
}

int	ft_herd_while_2(t_joins *stack_2, t_words *head, t_env **env, char *str)
{
	char	*tmp;

	if (head->is == 1)
	{
		(*env)->is = 1;
		char	*a = ft_strdup(head->word);
		tmp = dele_quotes(&a);
		if (tmp[0] == '$')
		{
			free(tmp);
			tmp = ft_strdup("");
		}
	}
	if (!str
		|| ((head->is && ft_strcmp(tmp, str) == 0)
			|| ft_strcmp(head->word, str) == 0))
	{
		if (head->is)
			free(tmp);
		free(str);
		return (1);
	}
	if (!str)
	{
		free(str);
		write(stack_2->out, "\n", 1);
		return (2);
	}
	if (!head->is)
	{
		char *po = ft_strjoin("\"", str);
		po = test(po, "\"");
		(*env)->is = 0;
		tmp = all_expand(po, *env);
		free(str);
		free(po);
		tmp = ft_remove_qoutes_herd(tmp);
		ft_print_free(tmp, stack_2->out);
	}
	else
	{
		free(tmp);
		ft_print_free(str, stack_2->out);
	}
	return (0);
}
