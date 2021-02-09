#include "../../includes/minishell.h"

void	call(char *cmd, char **args)
{
	char	**paths;
	char	*path;
	int		i;
	pid_t	pid;

	if ((pid = fork()) == 0)
	{
		paths = get_path();
		i = 0;
		while (paths[i])
		{
			path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
			execve(path, args, g_envs);
			i++;
		}
	}
	else
		wait(NULL);
}

t_cmd	*get_cmd(char *line)
{
	t_cmd	*cmd;
	size_t	i;
	int		start;

	if (!(cmd = (t_cmd *)malloc(sizeof(t_cmd))))
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmd));
	i = 0;
	start = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			start = 1;
		else if (start)
		{
			cmd->cmd = ft_substr(line, 0, i);
			cmd->args = ft_split(line, ' ');
			return (cmd);
		}
		i++;
	}
	cmd->cmd = ft_strdup(line);
	cmd->args = ft_split(line, ' ');
	return (cmd);
}