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

int	quotes(char **str)
{
	int	a;
	int	b;
	int	i;

	a = 0;
	b = 0;
	i = 0;
	while (str[0][i])
	{
		if (str[0][i] == '\"')
			a++;
		if (str[0][i] == '\'')
			b++;
		i++;
	}
	if (a % 2 != 0 || b % 2 != 0)
		return (0);
	else
		return (1);
}

void	multiple(char **str)
{
	int	i;

	i = 0;
	while (str[0][i])
	{
		if (str[0][i] == '\"')
		{
			i++;
			while (str[0][i] != '\"')
			{
				str[0][i] *= -1;
				i++;
			}
		}
		else if (str[0][i] == '\'')
		{
			i++;
			while (str[0][i] != '\'')
			{
				str[0][i] *= -1;
				i++;
			}
		}
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

static size_t	ft_strlcpy(char *dst, char *src, size_t size)
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
	ft_strlcpy(t_str, s1 + start, t_len + 1);
	return (t_str);
}

//end trime
void	back_to_string(t_words *words)
{
	while (words)
	{
		if (words->word[0] == '\'' || words->word[0] == '\"')
		{
			multiple(&words->word);
			words->word = ft_strtrim(words->word, "\'");
			words->word = ft_strtrim(words->word, "\"");
		}
		words = words->next;
	}
}

int	main(void)
{
	t_words	*words;
	t_joins	*tmp;
	char	*string;
	char	*str_sp;

	words = NULL;
	signal(SIGINT, ft_sighandler);
	rl_catch_signals = 0;
	while (1)
	{
		signal(SIGINT, ft_sighandler);
		string = readline("Minishell$ ");
		if (!string)
			break ;
		multiple(&string);
		if (quotes(&string) == 0)
			return (0);
		str_sp = ft_parsing(string);
		add_struct(str_sp, &words);
		if (!hundle_error(words))
			return (1);
		back_to_string(words);
		tmp = ft_parse_stack(&words);
	}
	return (0);
}
