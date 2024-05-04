#include "../minishell.h"

char	*ft_strdup(char *s1)
{
	int		i;
	char	*dst;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	dst = (char *)malloc(i + 1);
	if (!dst)
		return (NULL);
	dst[i] = '\0';
	i--;
	while (i >= 0)
	{
		dst[i] = s1[i];
		i--;
	}
	return (dst);
}

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

char	*ft_strlcpy(char **str, int len)
{
	int		i;
	char	*dst;

	i = 0;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	while (i < len)
		dst[i++] = *(*str)++;
	dst[i] = '\0';
	return (dst);
}

t_env	*ft_create_env_stack(char **env)
{
	t_env	*head;
	t_env	*node;
	char	*str;
	int		i;
	
	i = 0;
	(void)env;
	head = NULL;
	node = NULL;
	while (env[i])
	{
		str = env[i];
		node = ft_lstnew_env(ft_strlcpy(&str, ft_get_env_len(str, '=')), str);
		if (!node)
			return (NULL);
		ft_lstadd_back_env(&head, node);
		i++;
	}
	// while (head)
	// {
	// 	printf("{%s}  :  {%s}\n", head->key, head->value);
	// 	head = head->next;
	// }
	return (head);
}
