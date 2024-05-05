#include "../minishell.h"

void	ft_pwd(t_joins	**stack_2)
{
	char	buffer[1024];

	while (*stack_2)
		ft_next_node_joins(stack_2);
	getcwd(buffer, sizeof(buffer));
	ft_putstr(buffer, 1);
	ft_putstr("\n", 1);
}
