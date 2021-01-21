#include "../../includes/minishell.h"

void    ft_pipe(char *str)
{
    int pipefd[2];
    char *buf;
    int id;

    if (pipe(pipefd) == -1) 
        printf("erreur fonction pipe\n");
    id = fork();
    if (id == -1)
        printf("erreur fonction fork\n");
    //printf("hello from %d\n", id);
    if (id == 0) //le fils
    {
        close(pipefd[1]); //ferme le fd d'écriture du tube
        while (read(pipefd[0], &buf, 1) > 0) // lit dans le tube
            write(0, &buf, 1); //ecrit dans l'entrée standard ce qu'il a lu dans le tube
        write(0, "\n", 1);
        close(pipefd[0]); //ferme le fd de lecture du tube
    }
    else //le pere
    {
        close(pipefd[0]); //ferme le fd de lecture du tube
        write(pipefd[1], str, ft_strlen(str)); //ecrit dans le tube
        close(pipefd[1]); //ferme le fd decriture
        wait(NULL); //attend execution du fils
    }
}