#include "../minishell.h"

void	ft_pwd(t_joins	**stack_2)
{
	char	buffer[1024];

	while (*stack_2)
		ft_next_node_joins(stack_2);
	getcwd(buffer, sizeof(buffer));
	ft_putstr(buffer, (*stack_2)->out);
	ft_putstr("\n", (*stack_2)->out);
}
