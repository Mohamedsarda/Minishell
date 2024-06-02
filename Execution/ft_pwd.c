#include "../minishell.h"

void	ft_pwd(t_joins	**stack_2)
{
	char	buffer[1024];

	getcwd(buffer, sizeof(buffer));
	ft_putstr(buffer, (*stack_2)->out);
	ft_putstr("\n", (*stack_2)->out);
}
