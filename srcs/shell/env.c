#include "../../includes/minishell.h"

ssize_t	find_env(char *env)
{
	size_t	i;	
	size_t	len;

	if (!env)
		return (-1);
	len = ft_strlen(env);
	i = 0;	
	while (g_envs[i])
	{
		if (!ft_strncmp(g_envs[i], env, len))
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env(char *env)
{
	ssize_t	i;
	size_t	len;

	if (!env)
		return (NULL);
	len = ft_strlen(env);
	if ((i = find_env(env)) != -1)
		return (ft_substr(g_envs[i], (len + 1), ft_strlen(g_envs[i])));
	return (NULL);
}

char	*set_env(char *env, char *new_env)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(env);
	if ((i = find_env(env)) != -1)
	{
		if (!(g_envs[i] = ft_strjoin(ft_substr(g_envs[i], 0, len + 1), new_env)))
			return (NULL);
		return (g_envs[i]);
	}
	return (NULL);
}

/*char	**get_path()
{
	size_t	i;

	if ((i = find_env("PATH")) != -1)
		return (ft_split(g_envs[i], ':'));
	return (NULL);
}*/

size_t	get_envs_count()
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
//		g_envs[i] = NULL;
//		free(g_envs[i]);
		i++;
	}
	new[size] = 0;
//	free(g_envs);
	return (new);
}

void	print_envs()
{
	size_t	i;

	i = 0;
	while (g_envs[i])
	{
		ft_putendl_fd(g_envs[i], 1);
		i++;
	}
}