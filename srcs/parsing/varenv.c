#include "../../includes/minishell.h"

int	    environnement(char *whole_cmd, t_copy *copy, int arg, int i)
{
	printf("appel a variable d'environnement\n");
	char *name;
    char *value;
    int count = -1;
    
    copy->i++;
    if (!(name = malloc(sizeof(char) * strlen(whole_cmd) + 1)))
		return (-1);
    if (!(value = malloc(sizeof(char) * strlen(whole_cmd) + 500))) //modifier pour allouer correctement
		return (-1);
    if (whole_cmd[copy->i] == '{')
        copy->i++;
    while(whole_cmd[copy->i] && (whole_cmd[copy->i] != '}' && whole_cmd[copy->i] != ' '))
    {
        name[++count] = whole_cmd[copy->i];
        copy->i++;
    }
    name[count + 1] = 0;
    if (whole_cmd[copy->i] == '}')
        copy->i++;
    value = get_env(name);
    printf("nom variable = %s\n", name);
    printf("value = %s\n", value);
    /*if (value && arg == 0)
    {
        copy->cmd[++copy->j] = value;
    }
    if (value && arg == 1)
    {
        copy->args[i][++copy->j] = value;
    }
    if (name)
        free(name);*/
    return(0);
}