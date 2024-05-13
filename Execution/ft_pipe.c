#include "../minishell.h"

void    ft_is_pipe(t_joins **head)
{
    (void)head;
    int p1 = fork();
    int p2 = fork();
    printf("%d", p1);
    printf("%d", p2);
}