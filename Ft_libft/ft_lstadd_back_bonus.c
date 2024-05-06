#include "../minishell.h"

void	ft_lstadd_back(t_words **head, t_words *node)
{
	t_words	*last;

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
