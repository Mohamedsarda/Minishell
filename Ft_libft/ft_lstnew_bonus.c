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
	int i = 0;
	while(content[i])
	{
		if(content[i] == '$')
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
char	*check_env(char *str, t_env *env)
{
	while (env)
	{
		if(!ft_strcmp(str, env->key))
			return (env->value);
		env = env->next;
	}
	return ("\0");
}

char	check_key(char c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		return ('\0');
	return (c);
}

char	*check_after_env(char **tmp)
{
	int i = 0;
	char c;
	char	*str;
	while(tmp[0][i])
	{
		c = check_key(tmp[0][i]);
		if(c)
		{
			str =ft_strlcpy(tmp, ft_get_env_len(*tmp, c));
			return (str);
		}
		i++;
	}
	return (*tmp);
}
char	*cpy(char	*str, int len)
{
	int		i;
	char	*dst;

	i = 0;
	str++;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	while (i < len)
		dst[i++] = *str++;
	dst[i] = '\0';
	return (dst);
}
char	*handle_env(t_words *node, char *content, t_env *env)
{
	char *str = NULL;
	(void)env;
	char	**tmp;
	int		j;
	char	*key;
	j = -1;

	if(node->type == 6)
	{
		str =ft_strlcpy(&content, ft_get_env_len(content, '$'));
		tmp = ft_split(content, '$');
		if (tmp == NULL || *tmp == NULL)
			return NULL;
		while (tmp[++j])
		{
			key = check_after_env(&tmp[j]);
			if(ft_strcmp(key, tmp[j]) == 0)
			{
				if(key[0] >= '0' && key[0] <= '9')
					str = cpy(key, ft_strlen(key) - 1);
				else
					str = ft_strjoin(str, check_env(key, env));
			}
			else
			{
				str = ft_strjoin(str, check_env(key, env));
				if(ft_strcmp(key, tmp[j]) != 0)
					str = ft_strjoin(str, tmp[j]);
			}
			node->type = 0;
		}
		return (str);
	}
	return (content);
}

t_words	*ft_lstnew(char *content, t_env *env_stack)
{
	t_words	*new_node;
	(void)env_stack;
	new_node = NULL;
	new_node = (t_words *)malloc(sizeof(t_words));
	new_node->word = malloc(ft_strlen(content) + 1);
	new_node->type = ft_check_type(content);
	content  = handle_env(new_node, content, env_stack);
	if (!new_node || !new_node->word)
		return (NULL);
	ft_memcpy(new_node->word, content, ft_strlen(content));
	new_node->next = NULL;
	return (new_node);
}
