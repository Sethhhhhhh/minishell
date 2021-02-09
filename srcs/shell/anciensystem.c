#include "../../includes/minishell.h"

char    **ft_cmd_args(char *cmd_path, char *arg)
{
    char **cmd_args;
    int i;

    i = 0;
    if (!(cmd_args = malloc(sizeof(char *) * 3)))
        return (0);
    while (++i < 3)
    {
        cmd_args[0] = cmd_path;
        cmd_args[1] = arg;
        if (arg == NULL)
            break;
        cmd_args[2] = NULL;
    }
    return (cmd_args);
}

int     sys_call(char *cmd, char **paths, char *arg, char **env)
{
    char *cmd_path;
    char **cmd_args;
    int i;
    int id;

    i = -1;
    id = fork();
    if (id == -1)
        printf("erreur fonction fork\n");
    if (id == 0) //le fils
    {
        while (paths[++i])
        {
            cmd_path = ft_strjoin(paths[i], "/");
            cmd_path = ft_strjoin(cmd_path, cmd);
            cmd_args = ft_cmd_args(cmd_path, arg);
            execve(cmd_path, cmd_args, env);
        }
        printf("cmd existe pas\n"); //ici car quand execve a trouvé le fichier il arrête d'exectuer le programme donc sil arrive ici c'est que la cmd est dans aucun path
    }
    else //le pere
        wait(NULL);
    return (-1);
}