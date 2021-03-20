/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:53:21 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 03:36:39 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		options_special_case(char *arg, t_copy *copy)
{
	int		i;

	i = copy->i - 1;
	if (!arg[0] && i >= 2 && (copy->wc[copy->i - 1] == '"'
		|| copy->wc[copy->i - 1] == '\'') && (copy->wc[copy->i - 2] == '"'
		|| copy->wc[copy->i - 2] == '\'') && !copy->wc[copy->i])
	{
		while (i >= 2 && (copy->wc[i] == '"' || copy->wc[i] == '\''))
		{
			if (copy->wc[i - 1] != copy->wc[i])
				return (0);
			i = i - 2;
		}
		if (copy->wc[i] != ' ')
			return (0);
		return (1);
	}
	return (0);
}

void	ft_copy_tmp(t_copy *copy, char **tmp, size_t j)
{
	while (j)
	{
		copy->args[j - 1] = ft_strdup(tmp[j - 1]);
		if (tmp[j - 1])
		{
			free(tmp[j - 1]);
		}
		j--;
	}
}

int		options(t_copy *copy, size_t i, size_t j)
{
	char	**tmp;
	char	*arg;

	arg = NULL;
	tmp = NULL;
	copy->args[0] = ft_strdup(copy->cmd);
	while (1)
	{
		tmp = copy->args;
		copy->args = (char **)malloc(sizeof(char *) * (i + 2));
		if (!(copy->args))
			return (-1);
		j = i;
		ft_copy_tmp(copy, tmp, j);
		if (tmp)
		{
			free(tmp);
		}
		arg = args(copy, i);
		if (g_error == -1)
		{
			copy->args[i + 1] = NULL;
			return (-1);
		}
		if (options_special_case(arg, copy) == 1)
			arg = args(copy, ++i);
		if ((!arg) || (!arg[0] && !copy->wc[copy->i]))
		{
			free(arg);
			break ;
		}
		i++;
	}
	copy->args[i] = NULL;
	return (1);
}
