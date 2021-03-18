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