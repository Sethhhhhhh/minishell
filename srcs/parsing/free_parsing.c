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
	if (copy->cmd)
	{
		//printf("copy->cmd : %p free\n", copy->cmd);
		free(copy->cmd);
	}
	if (copy->args)
	{
		while (copy->args[i])
		{
			//printf("copy->args[%d] : %p parsing free\n", i, copy->args[i]);
			free(copy->args[i]);
			i++;
		}
		//printf("copy->args char **: %p parsing free\n", copy->args);
		free(copy->args);
	}
	if (copy->redir.out1)
		free(copy->redir.out1);
	if (copy->redir.out2)
		free(copy->redir.out2);
	if (copy->redir.in)
		free(copy->redir.in);
}

/*void	free_list_pip(t_pip *pipcell)
{
	t_pip	*tmp;
	if (pipcell == NULL)
		return ;
	ft_putstr_fd("ca rentre2\n", 2);
	while (pipcell)
	{
		if (pipcell->cmd_pip)
			free(pipcell->cmd_pip);
		tmp = pipcell;
		printf("tmp t_pip : %p free\n", tmp);
		pipcell = pipcell->next;
		free(tmp);
	}
}*/

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
