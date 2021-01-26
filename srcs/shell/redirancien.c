#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void     redir()
{
    /*redirection de stdout*/
    int fd;
    int savestdout;
    savestdout = dup(1);
    close (1);
    fd = open("bonjour", O_WRONLY | O_CREAT, 777);
    dup2(fd, 1);
    write(1, "coucou", 6);
    dup2(savestdout, 1);
    write(1, "coucou2", 7);
    /*redirection de stdin*/
    int fd;
    int savestdin;
    char *buffer;
    savestdin = dup(0);
    close (0);
    fd = open("hey", O_RDONLY);
    //while (ret = read() != 0) //on lit tout et on met dans buffer
    //{
    //    //on envoie buffer en argument à cat
    //}
    dup2(fd, 0);
    dup2(savestdin, 0);
    /*redirection de stderr*/
    int fd;
    int savestderr;
    savestderr = dup(2);
    close (2);
    fd = open("errors", O_WRONLY | O_CREAT, 777);
    dup2(fd, 2);
    write(1, "erreur", 6);
    dup2(savestderr, 2);
    write(1, "ok", 7);
}