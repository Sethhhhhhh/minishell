#include "../../includes/minishell.h"

/*int		check_cmd(char *cmd, t_env *tenv)
{
	if (!ft_strcmp(cmd, "echo"))
		printf("OK\n");
	else if (!ft_strcmp(cmd, "cd"))
		printf("OK\n");	
	else if (!ft_strcmp(cmd, "pwd"))
		printf("OK\n");	
	else if (!ft_strcmp(cmd, "export"))
		printf("OK\n");	
	else if (!ft_strcmp(cmd, "unset"))
		printf("OK\n");	
	else if (!ft_strcmp(cmd, "env"))
		printf("OK\n");	
	else if (!ft_strcmp(cmd, "exit"))
		printf("OK\n");
	else if (sys_call(cmd, tenv->paths, NULL, tenv->env) == -1) //ici il faut s'occuper des arguments, j'ai mis NULL mais à changer
		return (0);
	else
		return (0);
	return (1);
}

char	*get_cmd(t_sep *cmd, t_env *tenv)
{
	char	*command;
	int		i;

	i = 0;
	while (cmd->cmd_line[i] && !ft_isspace(cmd->cmd_line[i]))
		i++;
	command = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (cmd->cmd_line[i] && !ft_isspace(cmd->cmd_line[i]))
	{
		command[i] = cmd->cmd_line[i];
		i++;
	}
	command[i] = '\0';
	if (!check_cmd(command, tenv))
		return (NULL);
	return (command);
}*/