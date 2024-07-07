/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msarda <msarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:40:13 by msarda            #+#    #+#             */
/*   Updated: 2024/07/07 22:40:13 by msarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_search_key(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = (*env);
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	ft_unset_while(t_env *tmp, t_env **env, t_env *cur, char *str)
{
	while (tmp && ft_search_key(env, str))
	{
		cur = tmp->next;
		if (ft_strcmp("_", str) == 0)
			return (0);
		if (ft_strcmp(str, cur->key) == 0)
		{
			tmp->next = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			break ;
		}
		tmp = tmp->next;
	}
	return (1);
}

static void	ft_printf_error_unset(t_env **env, char *str)
{
	ft_exit_status(env, "1");
	ft_putstr("Minishell$ unset: `", 2);
	ft_putstr(str, 2);
	ft_putstr("': not a valid identifier\n", 2);
}

static void	ft_unset_f(t_env **env, t_env *cur, t_env *tmp)
{
	cur = tmp;
	tmp = tmp->next;
	(*env) = (*env)->next;
	free(cur->key);
	free(cur->value);
	free(cur);
}

void	ft_unset(t_joins **head, t_env **env)
{
	int		i;
	t_env	*tmp;
	t_env	*cur;

	i = 1;
	cur = NULL;
	ft_exit_status(env, "0");
	while ((*head)->content[i])
	{
		tmp = (*env);
		if ((check_key_env((*head)->content[i])
				|| ft_strcmp((*head)->content[0], "?") == 0)
			&& (ft_strlen((*head)->content[i]) != 0 || (*head)->quotes == 1))
		{
			ft_printf_error_unset(env, (*head)->content[i]);
			i++;
			continue ;
		}
		if (ft_strcmp((*head)->content[i], tmp->key) == 0)
			ft_unset_f(env, cur, tmp);
		else
			if (ft_unset_while(tmp, env, cur, (*head)->content[i]) == 0)
				return ;
		i++;
	}
}
