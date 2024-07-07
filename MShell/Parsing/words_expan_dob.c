/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_expan_dob.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:42:03 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:42:04 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*real_expand_in_double(char *str, int *i, t_env *env, char *result)
{
	char	*key;
	char	*sta;
	char	*res;
	int		c;
	int		j;

	c = 0;
	j = 0;
	key = get_only_key(str, i);
	sta = check_env(key, env);
	res = malloc(ft_strlen(sta) + 1 + ft_strlen(result));
	if (!res)
		return (NULL);
	while (result != NULL && result[c])
	{
		res[c] = result[c];
		c++;
	}
	while (sta[j])
		res[c++] = sta[j++];
	res[c] = '\0';
	free(key);
	return (res);
}

char	*ft_expand_in_double(char *result, char *str, int *i, t_env *env)
{
	char	*res;

	res = NULL;
	(*i)++;
	if (str[*i] >= '0' && str[*i] <= '9')
		return ((*i)++, result);
	else if (str[*i] == '\"' || str[*i] == '\'')
		return (test_1(result, "$"));
	else if (str[*i] == '$')
		return ((*i)++, test_1(result, "$$"));
	else if (str[*i] == ' ' || str[*i] == '\t')
		return (test_1(result, "$"));
	else
	{
		res = real_expand_in_double(str, i, env, result);
		free(result);
		return (res);
	}
	return (result);
}
