/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:07:42 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/15 20:00:59 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	list_pipe(t_sep *list, t_copy *cmdarg, int *fdd)
{
	while (list->pipcell)
	{
		if (parsing(list->pipcell->cmd_pip, cmdarg) == NULL)
			break ;
		*fdd = run_pipe(list->pipcell, cmdarg, *fdd);
		list->pipcell = list->pipcell->next;
	}
	close(*fdd);
}

static void	clean_redir(t_copy *copy, int savein, int saveout1, int saveout2)
{
	if (copy->redir.in)
		dup2(savein, 0);
	if (copy->redir.out1)
		dup2(saveout1, 1);
	if (copy->redir.out2)
		dup2(saveout2, 2);
}

static void	redir_dup(t_copy *cmdarg)
{
	int		savein;
	int		saveout1;
	int		saveout2;

	savein = 0;
	if (cmdarg->redir.in != NULL)
	{
		savein = dup(0);
		close(0);
		dup2(cmdarg->redir.sstdin, 0);
	}
	if (cmdarg->redir.out1)
	{
		saveout1 = dup(1);
		close(1);
		dup2(cmdarg->redir.sstdout, 1);
	}
	if (cmdarg->redir.out2)
	{
		saveout2 = dup(2);
		close(2);
		dup2(cmdarg->redir.sstderr, 2);
	}
	exec(cmdarg->args, 0);
	clean_redir(cmdarg, savein, saveout1, saveout2);
}

void		minishell(t_sep *list)
{
	int		fdd;
	t_copy	cmdarg;
	int		i;

	fdd = dup(0);
	i = 0;
	while (list)
	{
		if (list->pipcell != NULL)
			list_pipe(list, &cmdarg, &fdd);
		else
		{
			if (parsing(list->cmd_sep, &cmdarg) == NULL)
				break ;
			execution(&cmdarg, 0);
		}
		list = list->next;
		i++;
	}
}

void		execution(t_copy *cmdarg, int pipe)
{
	if (cmdarg->redir.in || cmdarg->redir.out1 || cmdarg->redir.out2)
		redir_dup(cmdarg);
	else
		exec(cmdarg->args, pipe);
}
