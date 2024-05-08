#include "../minishell.h"

t_env	*ft_lstnew_env(char *val_1, char *val_2)
{
	t_env	*head;

	head = (t_env *)malloc(sizeof(t_env));
	if (!head)
		return (NULL);
	if (*val_2 == '=')
		val_2++;
	head->key = ft_strdup(val_1);
	head->value = ft_strdup(val_2);
	head->next = NULL;
	return (head);
}

void	ft_lstadd_back_env(t_env **head, t_env *node)
{
	t_env	*last;

	if (*head == NULL)
	{
		*head = node;
		return ;
	}
	if (!head || !node)
		return ;
	last = *head;
	while (last->next)
		last = last->next;
	last->next = node;
}

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

char	**ft_empty_env(char **env, int *tmp)
{
	int	j;

	j = 0;
	(*tmp) = 1;
	puts("------");
	env = (char **)malloc(5 * sizeof(char *));
	if (!env)
		return (NULL);
	env[j++] = ft_strdup("USER=msarda");
	env[j++] = ft_strdup("HOME=/Users/msarda");
	env[j++] = ft_strdup("SHLVL=1");
	env[j++] = ft_strdup("PATH=/Users/msarda/.brew/bin:/usr/local/bin:/usr/bin:/bin:/\
		usr/sbin:/sbin:/usr/local/munki:/Library/\
		Apple/usr/bin:/Users/msarda/.brew/bin");
	env[j] = NULL;
	return (env);
}

t_env	*ft_create_env_stack(char **env, int tmp)
{
	t_env	*head;
	t_env	*node;
	char	*str;
	char	*key;
	int		i;

	i = -1;
	if (!*env)
		env = ft_empty_env(env, &tmp);
	while (env[++i])
	{
		str = env[i];
		key = ft_strlcpy(&str, ft_get_env_len(str, '='));
		node = ft_lstnew_env(key, str);
		if (!node)
			return (free(key), NULL);
		free(key);
		ft_lstadd_back_env(&head, node);
	}
	i = -1;
	while (tmp && env[++i])
		free(env[i]);
	if (tmp)
		free(env);
	return (head);
}
