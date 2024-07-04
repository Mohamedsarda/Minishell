#include "../minishell.h"

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
	if (last)
		while (last->next)
			last = last->next;
	last->next = node;
}

char	**ft_empty_env(char **env, int *tmp)
{
	int		j;
	char	buffer[1024];

	getcwd(buffer, sizeof(buffer));
	j = 0;
	(*tmp) = 1;
	env = (char **)malloc(5 * sizeof(char *));
	if (!env)
		return (NULL);
	env[j++] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	env[j++] = ft_strjoin("PWD=", buffer);
	env[j++] = ft_strdup("SHLVL=1");
	env[j++] = ft_strdup("_=");
	env[j] = NULL;
	return (env);
}

int	ft_atoi1(char *s)
{
	int	i;
	int	nmbr;

	i = 0;
	nmbr = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] == '=')
		i++;
	if (s[i] == '-')
		return (-1);
	if (s[i] == '+')
		i++;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			nmbr = nmbr * 10 + (s[i] - '0');
		else
			break ;
		i++;
	}
	if (s[i] != '\0' || nmbr > 999)
		return (9999);
	if (nmbr == 999)
		return (10000);
	return (nmbr);
}

void	ft_shelvl(char *str, char *key, t_env **node)
{
	int		a;

	a = 0;
	a = ft_atoi1(str);
	if (a == 9999)
		str = ft_itoa(1);
	else if (a == 10000)
		str = ft_strdup("");
	else
		str = ft_itoa(a + 1);
	(*node) = ft_lstnew_env(key, str);
	(*node)->equal = 1;
	free(str);
}

int	ft_get_env_data(t_env **node, char *str, int tmp)
{
	char	*key;

	key = ft_strlcpy(&str, ft_get_env_len(str, '='));
	if (ft_strcmp(key, "SHLVL") == 0)
		ft_shelvl(str, key, node);
	else if (ft_strcmp(key, "OLDPWD") == 0)
	{
		str = ft_strdup("");
		(*node) = ft_lstnew_env(key, str);
		free(str);
		(*node)->print = 1;
	}
	else
		(*node) = ft_lstnew_env(key, str);
	if (tmp && ft_strcmp("PATH", key) == 0)
		(*node)->print = 0;
	free(key);
	if (!(*node))
		return (0);
	return (1);
}

t_env	*ft_create_env_stack(char **env, int tmp)
{
	t_env	*head;
	t_env	*node;
	int		i;

	i = -1;
	node = NULL;
	if (!*env)
		env = ft_empty_env(env, &tmp);
	while (env[++i])
	{
		if (ft_get_env_data(&node, env[i], tmp) == 0)
			return (NULL);
		ft_lstadd_back_env(&head, node);
	}
	node = ft_lstnew_env("?", "=0");
	if (!node)
		return (NULL);
	node->print = 0;
	ft_lstadd_back_env(&head, node);
	i = -1;
	while (tmp && env[++i])
		free(env[i]);
	if (tmp)
		free(env);
	return (head);
}
