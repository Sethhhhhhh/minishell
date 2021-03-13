/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:48:24 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/13 14:23:42 by seth             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	set_env(char *env, char *new_env)
{
	char	*tmp;
	ssize_t	i;
	size_t	len;

	len = ft_strlen(env);
	i = -1;
	if ((i = find_env(env)) != -1)
	{
		tmp = ft_substr(g_envs[i], 0, len + 1);
		if (!(g_envs[i] = ft_strjoin(tmp, new_env)))
		{
			free(tmp);
			return (0);
		}
		free(tmp);
		return (1);
	}
	else
	{
		len = get_envs_count() + 1;
		g_envs = realloc_envs(len);
		tmp = ft_strjoin(env, "=");
		g_envs[len - 1] = ft_strjoin(tmp, new_env);
		free(tmp);
		return (1);
	}
	return (0);
}

char	**get_path(void)
{
	char	*path;

	if ((path = get_env("PATH")))
		return (ft_split(path, ':'));
	return (NULL);
}

size_t	get_envs_count(void)
{
	size_t	count;

	count = 0;
	while (g_envs[count])
		count++;
	return (count);
}

char	**realloc_envs(size_t size)
{
	char	**new;
	size_t	i;

	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (g_envs[i] && i < size)
	{
		new[i] = ft_strdup(g_envs[i]);
		i++;
	}
	new[size] = 0;
	return (new);
}

void	print_envs(void)
{
	size_t	i;

	i = 0;
	while (g_envs[i])
	{
		ft_putendl_fd(g_envs[i], 1);
		i++;
	}
}
