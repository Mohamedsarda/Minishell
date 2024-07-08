/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:41:48 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:41:49 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_single_parssing(char *result, char *str, int *i)
{
	int		j;
	char	*res;
	int		c;

	j = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	res = malloc((*i - j) + 1 + ft_strlen(result) + 2);
	if (!res)
		return (NULL);
	c = 0;
	while (result != NULL && result[c])
	{
		res[c] = result[c];
		c++;
	}
	res[c++] = '\'';
	while (str[j] && str[j] != '\'')
		res[c++] = str[j++];
	res[c++] = '\'';
	res[c] = '\0';
	free(result);
	return (res);
}

static t_words	*ft_lstnew(t_words **head, char *content, t_env *env_stack)
{
	t_words	*new_node;
	char	*str;

	str = NULL;
	new_node = NULL;
	new_node = (t_words *)malloc(sizeof(t_words));
	if (!new_node)
		return (NULL);
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

static int	ft_add(t_words **head, char *str, t_env *env_stack)
{
	t_words	*node;

	multiple(&str, 0);
	if (str[0] == '<' && str[1] == '<')
		return (1);
	node = ft_lstnew(head, str, env_stack);
	ft_lstadd_back(head, node);
	return (0);
}

static t_words	*ft_lstnew_herd(char *val_1)
{
	t_words	*head;

	multiple(&val_1, 0);
	head = NULL;
	head = (t_words *)malloc(sizeof(t_words));
	if (!head)
		return (NULL);
	head->type = ft_check_type(NULL, val_1);
	if (check_double_qout(val_1))
		head->is = 1;
	else
		head->is = 0;
	head->word = ft_strdup(val_1);
	head->next = NULL;
	return (head);
}

void	add_struct(char *str, t_words **words, t_env *env_stack)
{
	char	**tmp;
	int		j;
	t_words	*node;

	j = 0;
	multiple(&str, 0);
	tmp = ft_split(str, ' ');
	if (tmp == NULL || *tmp == NULL)
		return ;
	while (tmp[j])
	{
		if (ft_add(words, tmp[j], env_stack))
		{
			node = ft_lstnew(words, tmp[j], env_stack);
			ft_lstadd_back(words, node);
			if (tmp[++j])
			{
				node = ft_lstnew_herd(tmp[j]);
				ft_lstadd_back(words, node);
			}
		}
		if (tmp[j])
			j++;
	}
	free_split(tmp);
}
