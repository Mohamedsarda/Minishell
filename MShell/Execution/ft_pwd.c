#include "../minishell.h"

char	*ft_pwd(t_joins	**stack_2, int is)
{
	char	buffer[1024];

	getcwd(buffer, sizeof(buffer));
	if (is)
		return (ft_strdup(buffer));
	else
	{
		ft_putstr(buffer, (*stack_2)->out);
		ft_putstr("\n", (*stack_2)->out);
	}
	return (NULL);
}
