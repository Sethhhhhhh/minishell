/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:53:21 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/13 12:54:45 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sep	*create_cell(char *cmd_sep)
{
	t_sep	*cell;

	cell = malloc(sizeof(t_sep));
	//printf("cell t_sep %p malloc\n", cell);
	if (!(cell))
		return (NULL);
	cell->prev = NULL;
	cell->next = NULL;
	cell->pipcell = NULL;
	cell->cmd_sep = cmd_sep;
	return (cell);
}

t_sep	*add_cell(t_sep *list, char *cmd_sep, int pos)
{
	t_sep	*prec;
	t_sep	*cur;
	t_sep	*cell;
	int		i;

	cur = list;
	i = 0;
	cell = create_cell(cmd_sep);
	if (list == NULL)
		return (cell);
	while (i < pos)
	{
		i++;
		prec = cur;
		cur = cur->next;
	}
	prec->next = cell;
	cell->next = cur;
	return (list);
}

void	print_list(t_sep *list)
{
	int		i;

	i = 0;
	while (list)
	{
		printf("-----------------------------------\n");
		printf("| i = %d                            \n", i);
		printf("| list->cmd_sep : %s            \n", list->cmd_sep);
		if (list->pipcell != NULL)
			print_pip_list(list->pipcell);
		printf("-----------------------------------\n");
		list = list->next;
		i++;
	}
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


