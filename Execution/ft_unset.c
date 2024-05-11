#include "../minishell.h"

void    ft_unset(t_joins **head, t_env **env)
{
    int     i;
    t_env   **tmp;

    tmp = env;
    i = 1;
    while((*head)->content[i])
    {
        while((*env))
        {
            if(ft_strcmp((*head)->content[i], (*env)->key) == 0)
            {
                if (!env)
                    return ;
                tmp = *env;
                *env = (*env)->next;
                free((*tmp)->key);
                free((*tmp)->value);
                free((*tmp));
            }
            (*env) = (*env)->next;
        }
        i++;
    }
}