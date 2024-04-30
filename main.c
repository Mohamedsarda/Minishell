
#include "minishell.h"

void ft_sighandler(int i)
{
	(void)i;
    rl_catch_signals = 0;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}


int quotes(char **str)
{
	int a = 0;
	int b = 0;
	int i = 0;
	while (str[0][i])
	{
		if(str[0][i] == '\"')
			a++;
		if(str[0][i] == '\'')
			b++;
		i++;
	}
	if(a % 2 != 0 || b % 2 != 0 )
		return 0;
	else
		return 1;
}
void multiple(char **str)
{
	int i = 0;
	while(str[0][i])
	{
		if(str[0][i] == '\"')
		{
			i++;
			while(str[0][i] != '\"')
			{
				str[0][i] *= -1;
				i++;
			}
		}
		i++;
	}
}

int main()
{
	t_words *words;
	t_joins *tmp;
	char *string;

	words = NULL;
	(void)tmp;
	signal(SIGINT, ft_sighandler);
    rl_catch_signals = 0;
	while (1)
	{
		signal(SIGINT, ft_sighandler);
		string = readline("jjjj > ");
		if(!string)
			break;
		multiple(&string);
		if(quotes(&string) == 0)
			return (0);
		char *str_sp = ft_parsing(string);
		add_struct(str_sp, &words);
		if (!hundle_error(words))
			return (1);
		tmp = ft_parse_stack(&words);
	}
	return (0);
}