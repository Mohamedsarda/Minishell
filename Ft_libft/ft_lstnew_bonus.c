#include "../minishell.h"

static void	*ft_memcpy(void *dest, const void *src, size_t n)
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

static int	ft_check_type(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '$')
			return (6);
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

t_words	*ft_lstnew(char *content, t_env *env_stack)
{
	t_words	*new_node;

	new_node = NULL;
	new_node = (t_words *)malloc(sizeof(t_words));
	new_node->word = malloc(ft_strlen(content) + 1);
	new_node->type = ft_check_type(content);
	content = handle_env(new_node, content, env_stack);
	if (!new_node || !new_node->word)
		return (NULL);
	ft_memcpy(new_node->word, content, ft_strlen(content));
	new_node->next = NULL;
	return (new_node);
}
