#include "../includes/minishell.h"

static void	check(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->cmd, "echo", 4))
		_echo(cmd->args);
	else if (!ft_strncmp(cmd->cmd, "cd", 2))
		_cd(cmd->args);
	else if (!ft_strncmp(cmd->cmd, "pwd", 3))
		_pwd();
	else if (!ft_strncmp(cmd->cmd, "env", 3))
		_env();
	else if (!ft_strncmp(cmd->cmd, "unset", 5))
		_unset(cmd->args);
	else if (!ft_strncmp(cmd->cmd, "export", 6))
		_export(cmd->args);
	else
		call(cmd->cmd, cmd->args);
}

int		main_yohann(int ac, char **av, char **envs)
{
	t_cmd	*cmd;
	char	*line;
	g_envs = envs;

	while (1)
	{
		ft_putstr_fd(get_env("PWD"), 1);
		ft_putstr_fd("$ ", 1);
		get_next_line(1, &line);
		cmd = get_cmd(line);
		check(cmd);
	}
	return (0);
}