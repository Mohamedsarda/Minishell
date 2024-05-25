#include "../minishell.h"

int ft_joinssize(t_joins *head)
{
    int i;

    i = 0;
    while (head)
    {
        i++;
        head = head->next;
    }
    return (i);
}

void    ft_is_pipe(t_joins **head)
{
    
}
// void    ft_is_pipe(t_joins **head)
// {
//     int size = ft_joinssize(*head);
//     int pids[size];
//     int pipes[size + 1][2];
//     int i;
//     for (i = 0; i < size + 1; i++) {
//         if (pipe(pipes[i]) == -1) {
//             printf("Error with creating pipe\n");
//             return ;
//         }
//     }

//     for (i = 0; i < size; i++) {
//         pids[i] = fork();
//         if (pids[i] == -1) {
//             printf("Error with creating process\n");
//             return ;
//         }
//         if (pids[i] == 0) {
//             // Child process
//             int j;
//             for (j = 0; j < size + 1; j++) {
//                 if (i != j) {
//                     close(pipes[j][0]);
//                 }
//                 if (i + 1 != j) {
//                     close(pipes[j][1]);
//                 }
//             }
//             int x;
//             if (read(pipes[i][0], &x, sizeof(int)) == -1) {
//                 printf("Error at reading\n");
//                 return ;
//             }
//             printf("(%d) Got %d\n", i, x);
//             x++;
//             if (write(pipes[i + 1][1], &x, sizeof(int)) == -1) {
//                 printf("Error at writing\n");
//                 return ;
//             }
//             printf("(%d) Sent %d\n", i, x);
//             close(pipes[i][0]);
//             close(pipes[i + 1][1]);
//             return ;
//         }
//     }

//     // Main process
//     int j;
//     for (j = 0; j < size + 1; j++) {
//         if (j != size) {
//             close(pipes[j][0]);
//         }
//         if (j != 0) {
//             close(pipes[j][1]);
//         }
//     }
//     int y = 5;
//     if (write(pipes[0][1], &y, sizeof(int)) == -1) {
//         printf("Error at writing\n");
//         return ;
//     }
//     if (read(pipes[size][0], &y, sizeof(int)) == -1) {
//         printf("Error at reading\n");
//         return ;
//     }
//     close(pipes[0][1]);
//     close(pipes[size][0]);

//     for (i = 0; i < size; i++) {
//         wait(NULL);
//     }
//     return ;
// }