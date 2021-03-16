/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strip_extra_spaces_before.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:53:21 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/13 12:54:45 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				follow_env(int v, char *whole_cmd)
{
	v--;
	while (whole_cmd[v] && whole_cmd[v] != ' ')
	{
		if (whole_cmd[v] == '$' && whole_cmd[v - 1] != '\\')
			return (1);
		v--;
	}
	return (0);
}

int				add_space_before_condition(char *whole_cmd, int v)
{
	if (follow_env(v, whole_cmd) || whole_cmd[v - 1] == '"' || whole_cmd
		[v - 1] == '\'' || whole_cmd[v - 1] == '/' || whole_cmd[v - 1] ==
		'@' || whole_cmd[v - 1] == ',' || whole_cmd[v - 1] == '[' ||
		whole_cmd[v - 1] == ']' || (whole_cmd[v - 1] == ' ' &&
		whole_cmd[v - 2] == '\\'))
		return (1);
	return (0);
}

int				add_space_before_util(char *whole_cmd, int v, char *tmp)
{
	if (whole_cmd[v + 1] == ' ' && only_spaces(tmp))
		return (-1);
	while (whole_cmd[v] && whole_cmd[v] != '$' && whole_cmd[v - 1] != '\\')
		v--;
	if (whole_cmd[v - 1] == ' ' && only_spaces(tmp))
		return (-1);
	return (v);
}

int				add_space_before(char *tmp, char *whole_cmd, int v, char **new)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	copy = ft_strdup(*new);
	v--;
	if (tmp[i] == ' ')
	{
		v = add_space_before_util(whole_cmd, v, tmp);
		if (v == -1)
			return (-1);
		if (add_space_before_condition(whole_cmd, v) == 1)
		{
			while (copy[j])
			{
				(*new)[0] = ' ';
				(*new)[j + 1] = copy[j];
				j++;
			}
			(*new)[j + 1] = '\0';
		}
	}
	return (1);
}
