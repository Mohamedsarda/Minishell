#include "../minishell.h"

void ft_exit(t_joins **head, t_env **env)
{
    ft_lstclear_env(env);
    ft_lstclear_joins(head);
    exit(0);
}