#include "../../includes/minishell.h"

int	    environnement(char *whole_cmd, t_copy *copy, int arg, int i)
{
	printf("appel a variable d'environnement\n");
	char *nom;
    int count = -1;
    nom = NULL;
    
    copy->i++;
    if (!(nom = malloc(sizeof(char) * strlen(whole_cmd) + 1)))
		return (-1);
    if (whole_cmd[copy->i] == '{')
        copy->i++;
    while(whole_cmd[copy->i] && (whole_cmd[copy->i] != '}' && whole_cmd[copy->i] != ' '))
    {
        nom[++count] = whole_cmd[copy->i];
        copy->i++;
    }
    nom[count + 1] = 0;
    if (whole_cmd[copy->i] == '}')
        copy->i++;
    printf("nom variable = %s\n", nom);
    //appeler la fonction qui me renvoie la valeur qui correspond à la variable d'environnement
    //Si variable d'environnement existe pas ? on fait copy->i++ si whole_cmd[copy->i] == '}' et on return
    //if arg ==  0 : mettre dans mon copy->cmd[++copy->j] = valeur de la variable d'environnement
    //if arg ==  1 : mettre dans mon copy->args[i][++copy->j] = valeur de la variable d'environnement
    //free nom

    return(0);
}