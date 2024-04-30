
#include "../minishell.h"

//strlen(string)
void    check_symbols(char *str, int *i)
{
	if (*str == '|')
	{
		if (*(str - 1) != ' ')
			*i += 1;
		if (*(str + 1) != ' ')
			*i += 1;
	}
	if (*str == '$')
	{
		if (*(str - 1) != ' ')
			*i += 1;
		if (*(str + 1) != ' ')
			*i += 1;
	}
}

void check_REDIN_OU(char *str, int *i)
{
	if (*str == '>')
	{
		if (*(str - 1) != ' ' && *(str - 1) != '>')
			*i += 1;
		if (*(str + 1) != ' ' && *(str + 1) != '>')
			*i += 1;
	}
	else if (*str == '<')
	{
		if (*(str - 1) != ' ' && *(str + 1) != '<')
			*i += 1;
		if (*(str + 1) != ' ' && *(str + 1) != '<')
			*i += 1;
	}
}

int    ft_strlen_str_sp(char *str)
{
	int    i;

	i = 0;
	while (*str)
	{
	  if(*str == '|' || *str == '>'|| *str == '<' || *str == '$')
	  {
		check_symbols(str, &i);
		check_REDIN_OU(str, &i);
	  }
	  str++;
		i++;
	}
	return (i);
}
//end strlen(string)

// parsing

void    check_left_symbols(char **str, char **str_sp)
{
    if (**str == '|')
    {
        if (*((*str) - 1) != ' ' && *((*str) - 1) != '\0')
        {
            **str_sp = ' ';
            (*str_sp)++;
        }
    }
    else if (**str == '$')
    {
        if (*((*str) - 1) != ' ' && *((*str) - 1) != '\0')
        {
            **str_sp = ' ';
            (*str_sp)++;
        }
    }
    else if (**str == '>')
    {
        if (*((*str) - 1) != ' ' && *((*str) - 1) != '\0' && *((*str) - 1) != '>')
        {
            **str_sp = ' ';
            (*str_sp)++;
        }
    }
    else if (**str == '<')
    {
        if (*((*str) - 1) != ' ' && *((*str) - 1) != '\0' && *((*str) - 1) != '<')
        {
            **str_sp = ' ';
            (*str_sp)++;
        }
    }
}

void    check_right_symbols(char **str, char **str_sp)
{
    if (**str == '|')
    {
        if (*((*str) + 1) != ' ' && *((*str) + 1) != '\0')
        {
            **str_sp = ' ';
            (*str_sp)++;
        }
    }
    else if (**str == '$')
    {
        if (*((*str) + 1) != ' ' && *((*str) + 1) != '\0')
        {
            **str_sp = ' ';
            (*str_sp)++;
        }
    }
    else if (**str == '>')
    {
        if (*((*str) + 1) != ' ' && *((*str) + 1) != '\0' && *((*str) + 1) != '>')
        {
            **str_sp = ' ';
            (*str_sp)++;
        }
    }
    else if (**str == '<')
    {
        if (*((*str) + 1) != ' ' && *((*str) + 1) != '\0' && *((*str) + 1) != '<')
        {
            **str_sp = ' ';
            (*str_sp)++;
        }
    }
} 


char    *ft_parsing(char *str)
{
    char    *str_sp;
    str_sp = malloc(ft_strlen_str_sp(str) + 1);
    char *t = str_sp;
    while (*str)
    {
        if(*str == '|' || *str == '>'|| *str == '<' || *str == '$')
            check_left_symbols(&str, &str_sp);
            
        *str_sp = *str;
        str_sp++;
        if(*str == '|' || *str == '>'|| *str == '<' || *str == '$')
        {
            check_right_symbols(&str, &str_sp);
        }
        str++;
    }
    *str_sp = '\0';
    return (t);
}

// endparsing

// add to 1_stuck
static int	ft_add(t_words **head, char *a)
{
	t_words	*node;

	node = ft_lstnew(a);
	ft_lstadd_back(head, node);
	return (0);
}

static void	free_split(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
}

void	add_struct(char *str, t_words **words)
{
	char	**tmp;
	int		j;

	j = -1;
	tmp = ft_split(str, ' ');
	if (tmp == NULL || *tmp == NULL)
		return ;
	while (tmp[++j])
		ft_add(words, tmp[j]);
	free_split(tmp);
}
// end add to 1_stuck


