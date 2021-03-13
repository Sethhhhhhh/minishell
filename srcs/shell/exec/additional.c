/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:20:10 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/12 22:26:56 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	check_status(void)
{
	if (WIFEXITED(g_pid))
		g_status = WEXITSTATUS(g_pid);
	if (WIFSIGNALED(g_pid))
	{
		g_status = WTERMSIG(g_pid);
		if (g_status != 131)
			g_status += 128;
	}
	g_pid = 0;
}

int			run(char **args, char *bin, int pipe)
{
	if (!pipe)
		g_pid = fork();
	if (!pipe && g_pid < 0)
	{
		free(bin);
		ft_putstr_fd("minishell: execve: failed to create a new process.\n", 2);
		g_status = 1;
		return (-1);
	}
	else if (!g_pid)
		execve(bin, args, g_envs);
	free(bin);
	if (pipe)
		return (1);
	signal(SIGINT, SIG_IGN);
	wait(&g_pid);
	check_status();
	return (1);
}

int			has_perm(char **args, char *bin, struct stat statbuf, int pipe)
{
	if (statbuf.st_mode & S_IFREG)
	{
		if (statbuf.st_mode & S_IXUSR)
			return (run(args, bin, pipe));
		else
		{
			ft_putstr_fd("minishell: execve: permission denied: ", 2);
			ft_putstr_fd(bin, 2);
			ft_putchar_fd('\n', 2);
			g_status = 1;
		}
		free(bin);
		return (1);
	}
	else
	{
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		g_status = 1;
	}
	free(bin);
	return (1);
}

int			check_bins(char **args, int pipe)
{
	struct stat statbuf;
	char		**path;
	char		*bin;
	char		*tmp;
	size_t		i;

	path = ft_split(get_env("PATH"), ':');
	if (!path)
		return (-1);
	i = -1;
	while (path[++i])
	{
		bin = ft_strjoin(path[i], "/");
		tmp = bin;
		bin = ft_strjoin(bin, args[0]);
		free(tmp);
		if (!lstat(bin, &statbuf))
		{
			ft_free_array(path);
			return (has_perm(args, bin, statbuf, pipe));
		}
		free(bin);
	}
	ft_free_array(path);
	return (0);
}

int			check_builtin(char **args)
{
	if (ft_strequ(args[0], "echo"))
		return (run_echo(args));
	else if (ft_strequ(args[0], "cd"))
		return (run_cd(args));
	else if (ft_strequ(args[0], "unset"))
		return (run_unset(args));
	else if (ft_strequ(args[0], "export"))
		return (run_export(args));
	else if (ft_strequ(args[0], "exit"))
		run_exit(args);
	else if (ft_strequ(args[0], "pwd"))
	{
		ft_putstr_fd(getcwd(NULL, 0), 1);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if (ft_strequ(args[0], "env"))
	{
		run_env();
		return (1);
	}
	return (0);
}
