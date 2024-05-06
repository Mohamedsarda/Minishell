#include "minishell.h"

void	ft_sighandler(int i)
{
	(void)i;
	rl_catch_signals = 0;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	quotes(char *str)
{
	int	a;
	int	b;
	int	i;

	a = 0;
	b = 0;
	i = 0;
	while (*str && str[i])
	{
		if (str[i] == '\"')
			a++;
		if (str[i] == '\'')
			b++;
		i++;
	}
	if (a % 2 != 0 || b % 2 != 0)
		return (0);
	else
		return (1);
}

void	multiple(char **str, int is)
{
	int	i;

	if (!str || !*str)
		return ;
	i = 0;
	while (str && *str && str[0][i])
	{
		if (is == 0 && str[0][i] == '\"')
		{
			i++;
			while (str[0][i] && str[0][i] != '\"')
			{
				str[0][i] *= -1;
				i++;
			}
		}
		else if (str[0][i] == '\'')
		{
			i++;
			while (str[0][i] && str[0][i] != '\'')
			{
				str[0][i] *= -1;
				i++;
			}
		}
		if (!str[0][i])
			return ;
		i++;
	}
}
// trime

static void	*ft_memcpy(void *dest, void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

static size_t	ft_strlcpy_t(char *dst, char *src, size_t size)
{
	size_t	srclen;
	size_t	copy;

	srclen = ft_strlen(src);
	if (size > 0)
		copy = size - 1;
	else
		copy = 0;
	if (copy > srclen)
		copy = srclen;
	if (size > 0)
	{
		ft_memcpy(dst, src, copy);
		dst[copy] = '\0';
	}
	return (srclen);
}

static int	check_in_set(char c, char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	size_t	end;
	size_t	t_len;
	char	*t_str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && check_in_set(s1[start], set))
		start++;
	while (end > start && check_in_set(s1[end - 1], set))
		end--;
	t_len = end - start;
	t_str = (char *)malloc(t_len + 1);
	if (!t_str)
		return (NULL);
	ft_strlcpy_t(t_str, s1 + start, t_len + 1);
	free(s1);
	return (t_str);
}

//end trime

char *ft_rm_quotes(char *string, char c)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(string) - 1);
	while (string[i])
	{
		if (string[i] == c)
		{
			while (string[++i] != c)
				str[j++] = string[i];
		}
		else
			str[j++] = string[i];
		i++;
	}
	str[j] = '\0';
	free(string);
	return (str);
}

char	*back_to_string(char	*string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '\'')
		{
			multiple(&string, 0);
			return (string);
		}
		else if (string[i] == '\"')
		{
			multiple(&string, 0);
			return (string);
		}
		i++;
	}
	return (string);
}

void	ft_leaks(void)
{
	system("leaks minishell");
}

int	main(int ac, char **ar, char **env)
{
	t_words	*words;
	t_joins	*tmp;
	t_env	*env_stack;
	char	*string;
	char	*str_sp;

	(void)ar;
	if (ac != 1)
		return (1);
	tmp = NULL;
	atexit(ft_leaks);
	words = NULL;
	signal(SIGINT, ft_sighandler);
	rl_catch_signals = 0;
	(void)env_stack;
	env_stack = ft_create_env_stack(env, 0);
	while (1)
	{
		string = readline("Minishell$ ");
		string = ft_strtrim(string, " ");
		if (!string)
			break ;
		else if (!string[0])
		{
			free(string);
			continue ;
		}
		if (string[0] != '\0')
			add_history(string);
		multiple(&string, 0);
		if (quotes(string) == 0)
		{
			ft_putstr("Minishell : unexpected EOF while looking for matching `\"'\n", 2);
			free(string);
			continue ;
		}
		str_sp = ft_parsing(string);
		str_sp = back_to_string(str_sp);
		add_struct(str_sp, &words, env_stack);
		free(str_sp);
		if (!hundle_error(words))
		{
			ft_putstr("Minishell : syntax error near unexpected token `newline' \n", 2);
			ft_lstclear(&words);
			continue ;
		}
		tmp = ft_parse_stack(&words, env_stack);
	}
	ft_lstclear_joins(&tmp);
	ft_lstclear_env(&env_stack);
	rl_clear_history();
	return (0);
}
