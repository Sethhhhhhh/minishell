/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:34:32 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/15 19:57:49 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	status_child(pid_t	g_pid)
{
	int		g_status;

	if (WIFEXITED(g_pid))
		g_status = WEXITSTATUS(g_pid);
	if (WIFSIGNALED(g_pid))
	{
		g_status = WTERMSIG(g_pid);
		if (g_status != 131)
			g_status += 128;
	}
	return (g_status);
}

static void	child(t_pip *pipcell, int fd[2], int *fdd)
{
	close(fd[0]);
	close(0);
	dup(*fdd);
	close(*fdd);
	if (pipcell->next)
	{
		close(1);
		dup(fd[1]);
		close(fd[1]);
	}
}

int			run_pipe(t_pip *pipcell, t_copy *cmdargs, int fdd)
{
	int		fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (pipe(fd))
		return (-1);
	//printf("copy->cmd avant fork = %s / = %p\n", cmdargs->cmd, cmdargs->cmd);
	g_pid = fork();
	if (g_pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		close(fdd);
		return (-1);
	}
	else if (!g_pid)
	{
		child(pipcell, fd, &fdd);
		execution(cmdargs, 1);
		free_list_pip(pipcell);
		ft_exit(cmdargs);
	}
	wait(&g_pid);
	g_status = status_child(g_pid);
	close(fdd);
	close(fd[1]);
	//printf("copy->cmd après fork = %s / %p\n", cmdargs->cmd, cmdargs->cmd);
	return (fd[0]);
}
