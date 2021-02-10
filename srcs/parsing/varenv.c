#include "../../includes/minishell.h"

int    remalloc_cmd(t_copy *copy, char *value, char *whole_cmd)
{
    char *tmp;
    int i = -1;
    
    copy->cmd[copy->j + 1] = 0;
    tmp = ft_strjoin(copy->cmd, value);
    if (!(copy->cmd = malloc(sizeof(char) * (strlen(whole_cmd) + strlen(value) + 1))))
        return (-1);
    while (tmp[++i])
        copy->cmd[i] = tmp[i];
    copy->cmd[i] = 0;
    copy->j = strlen(copy->cmd);
    return (0);
}

int    remalloc_arg(t_copy *copy, char *value, char *whole_cmd, int i)
{
    char *tmp;
    int j = -1;
    
    tmp = NULL;
    copy->args[i][copy->j + 1] = 0;
    tmp = ft_strjoin(copy->args[i], value);
    if (!(copy->args[i] = malloc(sizeof(char) * (strlen(tmp) + 1))))
        return (-1);
    while (tmp[++j])
        copy->args[i][j] = tmp[j];
    copy->args[i][j] = 0;
    copy->j = strlen(copy->args[i]);
    return (0);
}

int	    environnement(char *whole_cmd, t_copy *copy, int arg, int i)
{
	char *name;
    char *value;
    int count = -1;

    if (!(name = malloc(sizeof(char) * strlen(whole_cmd) + 1)))
		return (-1);
    if (whole_cmd[++copy->i] == '{')
        copy->i++;
    while (whole_cmd[copy->i] && (whole_cmd[copy->i] != '}' && whole_cmd[copy->i] != ' ' && whole_cmd[copy->i] != '$'))
    {
        name[++count] = whole_cmd[copy->i];
        copy->i++;
    }
    name[count + 1] = 0;
    if (whole_cmd[copy->i] == '}')
        copy->i++;
    value = get_env(name);
    if (!value)
        return (0);
    if (arg == 0)
        remalloc_cmd(copy, value, whole_cmd);
    else
        remalloc_arg(copy, value, whole_cmd, i);
    if (whole_cmd[copy->i] == '$')
        return (1);
    return (0);
}