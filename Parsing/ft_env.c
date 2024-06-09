#include "../minishell.h"

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

// int ft_atoi1(char *s)
// {
// 	int i = 0;
// 	int nmbr = 0;
// 	while (s[i] && s[i] != '=')
// 		i++;
// 	if(s[i] == '=')
// 		i++;
// 	while(s[i])
// 	{
// 		if(s[i] >= '0' && s[i] <= '9')
// 			nmbr = nmbr *10 + (s[i] - '0');
// 		else
// 			break;
// 			i++;
// 	}
// 	if(s[i] != '\0'
// 	 || nmbr > 999)
// 		return (9999);
// 	if(nmbr == 999)
// 		return (10000);
// 	return (nmbr);
// }

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
		
		// if (ft_strcmp(key, "SHLVL") == 0)
		// {
		// 	printf("%s\n", str);
		// 	int a = ft_atoi1(str);
		// 	if(a == 9999)
		// 		str = ft_itoa(1);
		// 	else if(a == 10000)
		// 		str = ft_strdup("");
		// 	else
		// 		str = ft_itoa(a + 1);
		// 	node = ft_lstnew_env(key, str);
		// 	node->equal = 1;
		// 	free(str);
		// }
		if (ft_strcmp(key, "OLDPWD") == 0)
		{
			str = ft_strdup("");
			node = ft_lstnew_env(key, str);
			free(str);
			node->print = 1;
		}
		else
			node = ft_lstnew_env(key, str);
		if (tmp && ft_strcmp("PATH", key) == 0)
			node->print = 0;
		if (!node)
			return (free(key), NULL);
		free(key);
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
