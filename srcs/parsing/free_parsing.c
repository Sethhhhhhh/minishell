/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:07:42 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/15 20:00:59 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		free_cmdarg(t_copy *copy)
{
	int		i;

	i = 0;
	//	printf("copy->args[0] ap : %s\n", copy->args[0]);
	if (copy->cmd)
		free(copy->cmd);
	if (copy->args)
	{
		while (copy->args[i])
		{
				//printf("copy->args[%d]: %s\n", i, copy->args[i]);
				//printf("copy->args[%d] : %s parsing free\n", i, copy->args[i]);
				free(copy->args[i]);
				i++;
		}
		//printf("copy->args[%d]: %s\n", i, copy->args[i]);
		//printf("copy->args char **: %p parsing free\n", copy->args);
		free(copy->args);
		//printf("copy->args[%d]: %s\n", i, copy->args[i]);
	}
	if (copy->redir.out1)
		free(copy->redir.out1);
	if (copy->redir.out2)
		free(copy->redir.out2);
	if (copy->redir.in)
		free(copy->redir.in);
	copy->cmd = NULL;
	copy->args = NULL;
	copy->redir.out1 = NULL;
	copy->redir.out2 = NULL;
	copy->redir.in = NULL;
}

void	free_list_pip(t_pip *pipcell)
{
	t_pip	*tmp;
	if (pipcell == NULL)
		return ;
	while (pipcell)
	{
		if (pipcell->cmd_pip)
			free(pipcell->cmd_pip);
		tmp = pipcell;
		pipcell = pipcell->next;
		free(tmp);
	}
}

void	free_list(t_sep *list)
{
	t_sep	*tmp;

	if (list == NULL)
		return ;
	while (list)
	{
		if (list->cmd_sep)
			free(list->cmd_sep);
		//free_list_pip(list->pipcell);
		tmp = list;
		list = list->next;
		//printf("tmp t_sep : %p free\n", tmp);
		free(tmp);
	}
}
