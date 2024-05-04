#include "../minishell.h"

void	check_left_symbols(char **str, char **str_sp)
{
	if (**str == '|' && *((*str) - 1) != ' ' && *((*str) - 1) != '\0')
	{
		**str_sp = ' ';
		(*str_sp)++;
	}
	else if (**str == '>' && *((*str) - 1) != ' '
		&& *((*str) - 1) != '\0' && *((*str) - 1) != '>')
	{
		**str_sp = ' ';
		(*str_sp)++;
	}
	else if (**str == '<' && *((*str) - 1) != ' '
		&& *((*str) - 1) != '\0' && *((*str) - 1) != '<')
	{
		**str_sp = ' ';
		(*str_sp)++;
	}
}

void	check_right_symbols(char **str, char **str_sp)
{
	if (**str == '|' && *((*str) + 1) != ' ' && *((*str) + 1) != '\0')
	{
		**str_sp = ' ';
		(*str_sp)++;
	}
	else if (**str == '>' && *((*str) + 1) != ' '
		&& *((*str) + 1) != '\0' && *((*str) + 1) != '>')
	{
		**str_sp = ' ';
		(*str_sp)++;
	}
	else if (**str == '<' && *((*str) + 1) != ' '
		&& *((*str) + 1) != '\0' && *((*str) + 1) != '<')
	{
		**str_sp = ' ';
		(*str_sp)++;
	}
}

char	*ft_parsing(char *str)
{
	char	*str_sp;
	char	*t;
	char	*s;

	s = str;
	str_sp = malloc(ft_strlen_str_sp(str) + 1);
	t = str_sp;
	while (str && *str)
	{
		if (*str == '|' || *str == '>' || *str == '<')
			check_left_symbols(&str, &str_sp);
		*str_sp = *str;
		str_sp++;
		if (*str == '|' || *str == '>' || *str == '<')
		{
			check_right_symbols(&str, &str_sp);
		}
		str++;
	}
	*str_sp = '\0';
	free(s);
	return (t);
}
