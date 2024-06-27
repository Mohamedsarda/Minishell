#include "../minishell.h"

int	check_if_export(t_words **head, char *content)
{
	t_words	*a;

	if (head == NULL)
		return (6);
	a = *head;
	while (a)
	{
		if (!ft_strcmp(a->word, "export") && ft_strchr(content, '=') == 1)
			return (0);
		a = a->next;
	}
	return (6);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
	*d = '\0';
	return (dest);
}

int	ft_check_type(t_words **head, char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
		{
			if (check_if_export(head, content) == 0)
				return (0);
			return (6);
		}
		i++;
	}
	if (*content == '>' && *(content + 1) == '>')
		return (5);
	else if (*content == '<' && *(content + 1) == '<')
		return (4);
	else if (*content == '>')
		return (2);
	else if (*content == '<')
		return (1);
	else if (*content == '|')
		return (3);
	else
		return (0);
}

t_words	*ft_lstnew(t_words **head, char *content, t_env *env_stack)
{
	t_words	*new_node;
	char	*str;

	str = NULL;
	new_node = NULL;
	new_node = (t_words *)malloc(sizeof(t_words));
	new_node->type = ft_check_type(head, content);
	if ((content[0] == '\'' || content[0] == '\"')
		&& (content[ft_strlen(content) - 1] == '\''
			|| content[ft_strlen(content) - 1] == '\"'))
		new_node->is = 1;
	else
		new_node->is = 0;
	str = handle_env(new_node, content, env_stack);
	new_node->word = malloc(ft_strlen(str) + 1);
	if (!new_node || !new_node->word)
		return (NULL);
	ft_memcpy(new_node->word, str, ft_strlen(str));
	free(str);
	new_node->next = NULL;
	return (new_node);
}
