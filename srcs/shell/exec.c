#include "../../includes/minishell.h"

static int	_run(char **args, char *bin)
{
	g_pid = fork();
	if (!g_pid)
		execve(bin, args, g_envs);
	else if (g_pid < 0)
	{
		free(bin);
		ft_putstr_fd("execve: failed to create a new process.", 1);
		ft_putchar_fd('\n', 1);
		return (-1);
	}
	wait(&g_pid);
	free(bin);
	g_pid = 0;
	return (1);
}

static int	_has_perm(char **args, char *bin, struct stat statbuf)
{
	if (statbuf.st_mode & S_IFREG) // check if is not a folder.	
	{
		if (statbuf.st_mode & S_IXUSR) // check if the user can execute this file.
			return (_run(args, bin));
		else
		{
			ft_putstr_fd("execve: permission denied: ", 1);
			ft_putstr_fd(bin, 1);
			ft_putchar_fd('\n', 1);
		}
		free(bin);
		return (0);
	}
	free(bin);
	return (0);
}

static int	_check_bins(char **args)
{
	struct stat	statbuf;
	char		**path;
	char		*bin;
	char		*tmp;
	size_t		i;

	if (!(path = ft_split(get_env("PATH"), ':')))
		return (-1);
	i = 0;
	while (path[i])
	{
		bin = ft_strjoin(path[i], "/");
		tmp = bin;
		bin = ft_strjoin(bin, args[0]);
		free(tmp);
		if (!lstat(bin, &statbuf))
		{
			ft_free_array(path);
			return (_has_perm(args, bin, statbuf));
		}
		else
			free(bin);
		i++;
	}
	ft_free_array(path);
	return (0);
}

static int	_check_builtin(char **args)
{
	char	*str;

	if (ft_strequ(args[0], "echo"))
		return(run_echo(args));
	else if (ft_strequ(args[0], "cd"))
		return (run_cd(args));
	else if (ft_strequ(args[0], "unset"))
		return (run_unset(args));
	else if (ft_strequ(args[0], "export"))
		return (run_export(args));
	else if (ft_strequ(args[0], "pwd"))
	{
		if ((str = get_env("PWD")))
		{
			ft_putstr_fd(str, 1);
			ft_putchar_fd('\n', 1);
			return (1);
		}
	}
	else if (ft_strequ(args[0], "env"))
	{
		print_envs();
		return (1);
	}
	return (0);
}

int			exec(char **args)
{
	int		is_cmd;

	g_pid = 0;
	is_cmd = _check_builtin(args) || _check_bins(args);
	if (is_cmd > 0)
		return (1);
	else if (is_cmd < 0)
		return (-1);
	ft_putstr_fd("minishell: command not found: ", 1);
	ft_putstr_fd(args[0], 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
