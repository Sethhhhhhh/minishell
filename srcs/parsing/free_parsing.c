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
		free(copy->cmd);
	if (copy->args)
	{
		while (copy->args[i])
		{
			free(copy->args[i]);
			i++;
		}
		free(copy->args);
	}
	//if (copy->wc)
	//	free(copy->wc);
}