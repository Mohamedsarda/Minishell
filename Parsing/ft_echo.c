#include "../minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	if (n == 0)
		return (0);
	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((i < n - 1) && (str1[i] && str2[i]) && (str1[i] == str2[i]))
		i++;
	return (str1[i] - str2[i]);
}

void	ft_putstr_n(char *str, int fd)
{
	if (!str)
		return ;
	while (*str)
	{
		write(fd, str, 1);
		str++;
	}
}

void	ft_next_node_joins(t_joins **head)
{
	t_joins	*stack;
	int		i;

	stack = (*head)->next;
	i = 0;
	while ((*head)->content[i])
		free((*head)->content[i++]);
	free((*head)->content);
	free((*head));
	(*head) = stack;
}

void	ft_print_echo(char **str, int fd, int *i)
{
	while (str[(*i)])
	{
		ft_putstr_n(str[(*i)], fd);
		if (str[(*i) + 1])
			write(fd, " ", 1);
		(*i)++;
	}
}

void	ft_echo(t_joins **head)
{
	t_joins	*tmp;
	int		i;

	tmp = (*head);
	while (tmp)
	{
		i = 1;
		if (ft_strncmp(tmp->content[i], "-n", 2) == 0)
		{
			i++;
			ft_print_echo(tmp->content, tmp->out, &i);
		}
		else
		{
			ft_print_echo(tmp->content, tmp->out, &i);
			write(tmp->out, "\n", 1);
		}
		ft_next_node_joins(head);
		return ;
		tmp = tmp->next;
	}
}
