# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <signal.h>
# include <fcntl.h>

int main()
{
	char *str;

	while(1)
	{
		str = readline("ana");
	}
}
