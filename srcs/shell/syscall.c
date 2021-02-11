#include "../../includes/minishell.h"

void	call(t_copy *cmdarg)
{
	char	**paths;
	char	*path;
	int		i;
	int		status;

	if ((g_fork = fork()) < 0)
		exit(0);
	else if (!g_fork)
	{
		paths = get_path();
		i = 0;
		while (paths[i])
		{
			path = ft_strjoin(ft_strjoin(paths[i], "/"), cmdarg->cmd);
		//	printf("%s\n", path);
		//	printf("%s\n", cmdarg->args[1]);
			execve(path, cmdarg->args, g_envs);
			i++;
		}
	}
	else
		waitpid(g_fork, &status, 0);
	g_fork = 0;
}
