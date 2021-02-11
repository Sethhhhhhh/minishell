#include "../../includes/minishell.h"

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
}
