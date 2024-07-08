/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_part3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:40:00 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:40:02 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*delete_eq(char *str)
{
	char	*value;
	char	*tmp;
	int		i;

	i = 0;
	tmp = str;
	value = malloc(ft_strlen(tmp));
	if (!value)
		return (NULL);
	tmp++;
	while (*tmp)
	{
		value[i] = *tmp;
		tmp++;
		i++;
	}
	value[i] = '\0';
	free(str);
	return (value);
}

static void	ft_add_value_2(char *value, t_env *tmp, int append, char *t)
{
	if (append == 1)
	{
		value = delete_eq(value);
		tmp->print = 1;
		tmp->value = test(tmp->value, value);
		free(value);
	}
	else
	{
		if (!t)
			(tmp)->equal = 0;
		else if (t[0] == '=' && tmp->value != NULL)
		{
			t++;
			(tmp)->equal = 1;
		}
		free(tmp->value);
		tmp->value = ft_strdup(t);
		tmp->print = 1;
		free(value);
	}
}

static void	add_value(char *key, char *value, t_env **env, int append)
{
	t_env	*tmp;
	char	*t;

	tmp = (*env);
	t = value;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			ft_add_value_2(value, tmp, append, t);
			return ;
		}
		tmp = tmp->next;
	}
}

static char	*delete_plus(char *str)
{
	char	*value;
	char	*tmp;
	int		i;

	i = 0;
	tmp = str;
	if (*tmp == '+')
		value = malloc(ft_strlen(tmp));
	else
		value = malloc(ft_strlen(tmp) + 1);
	if (!value)
		return (NULL);
	if (*tmp == '+')
		tmp += 1;
	while (*tmp)
	{
		value[i] = *tmp;
		tmp++;
		i++;
	}
	value[i] = '\0';
	free(str);
	return (value);
}

void	work_export(char *key, char *value, t_env **env, int is)
{
	t_env	*node;

	node = NULL;
	if (is == 0)
	{
		if (check_key_in_path(key, env) == 1)
			add_value(key, value, env, 0);
		else
		{
			node = ft_lstnew_env(key, value);
			free(value);
			ft_lstadd_back_env(env, node);
		}
		return ;
	}
	value = delete_plus(value);
	if (check_key_in_path(key, env) == 1)
		add_value(key, value, env, 1);
	else
	{
		node = ft_lstnew_env(key, value);
		free(value);
		ft_lstadd_back_env(env, node);
	}
}
