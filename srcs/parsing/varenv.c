/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:53:21 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/13 12:54:45 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		multiple_dollars(t_copy *copy, int arg, int i)
{
	int		j;

	j = 0;
	while (copy->wc[copy->i] && copy->wc[copy->i] == '$' && (copy->wc
		[copy->i + 1] == '\0' || copy->wc[copy->i + 1] == '$' || copy->wc
		[copy->i - 1] == '$'))
	{
		if (arg == 0)
			copy->cmd[++copy->j] = copy->wc[copy->i];
		if (arg == 1)
			copy->args[i][++copy->j] = copy->wc[copy->i];
		copy->i++;
		j++;
	}
	if (j > 0)
	{
		copy->i--;
		return (1);
	}
	return (0);
}

int		find_name(t_copy *copy, int i, char **name)
{
	int		count;

	count = -1;
	if (i == 0)
		copy->i++;
	if (i == 0 && (copy->wc[copy->i] == '\'' || copy->wc[copy->i] == '"'))
	{
		copy->i--;
		return (0);
	}
	while (copy->wc[copy->i] && (copy->wc[copy->i] != '\\' && copy->wc
		[copy->i] != ' ' && copy->wc[copy->i] != '$' && copy->wc[copy->i]
		!= ']' && copy->wc[copy->i] != '[' && copy->wc[copy->i] != '"' &&
		copy->wc[copy->i] != ',' && copy->wc[copy->i] != '\'' && copy->wc
		[copy->i] != '/' && copy->wc[copy->i] != '=' && copy->wc[copy->i] !=
		'|' && copy->wc[copy->i] != '@'))
	{
		if (i == 0 && (copy->wc[copy->i] == '\'' || copy->wc[copy->i] == '"'))
			return (0);
		(*name)[++count] = copy->wc[copy->i];
		copy->i++;
	}
	(*name)[count + 1] = 0;
	return (1);
}

int		env(t_copy *copy, int arg, int i, int space)
{
	char	*name;
	char	*value;

	value = NULL;
	name = NULL;
	if (!(name = malloc(sizeof(char) * ft_strlen(copy->wc) + 1)))
		return (-1);
	if (multiple_dollars(copy, arg, i) != 0 || status_env(
		copy, arg, i) == 1)
		return (1);
	if (find_name(copy, 0, &name) != 1)
		return (0);
	value = get_env(name);
	if (space == 1 && value)
		value = ft_strip_extra_spaces(value, copy->wc, copy->i);
	if ((space = no_value(copy, value)) != 0)
		return (space);
	env_copy(copy, arg, i, value);
	copy->i--;
	return (1);
}

int		env_redir(t_copy *copy, int std, int spce)
{
	char	*name;
	char	*value;
	int		count;

	if (!(name = malloc(sizeof(char) * ft_strlen(copy->wc) + 1)))
		return (-1);
	copy->i++;
	if (copy->wc[copy->i] == '\'' || copy->wc[copy->i] == '"')
		return (0);
	if (status_env(copy, std + 2, 0) == 1)
		return (1);
	find_name(copy, 1, &name);
	value = get_env(name);
	if (spce == 1 && value)
		value = ft_strip_extra_spaces(value, copy->wc, copy->i);
	if (value && spce == 1 && (only_spaces(value) || ft_space_in_middle(value)))
		error_ambiguous(name);
	if (!value && spce == 1)
		error_ambiguous(name);
	if ((count = no_value(copy, value)) != 0)
		return (count);
	env_copy(copy, std + 2, 0, value);
	copy->i--;
	return (1);
}
