
#include "minishell.h"

void ft_sighandler(int i)
{
	(void)i;
    rl_catch_signals = 0;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    // rl_catch_signals = 1;
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
		char *str_sp = ft_parsing(string);
		add_struct(str_sp, &words);
		tmp = ft_parse_stack(&words);
	}
	return (0);
}