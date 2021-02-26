#include "../../includes/minishell.h"

static char	**remove_env(ssize_t index)
{
	size_t	i;
	size_t	size;

	i = index;
//	free(g_envs[index]);
//	envs[index] = NULL;
	size = get_envs_count();
	while (g_envs[i + 1])
	{
		g_envs[i] = ft_strdup(g_envs[i + 1]);
//		g_envs[i + 1] = NULL;
	//	free(envs[i + 1]);
		i++;
	}
	return (realloc_envs((size - 1)));
}

int			run_unset(char **args)
{
	size_t	i;
	ssize_t	index;

	if (!args[1])
		return (1);
	i = 1;
	while (args[i])
	{
		if ((index = find_env(args[i])) != -1)
		{
			if (g_envs[index])
				g_envs = remove_env(index);
		}
		else
		{
			ft_putstr_fd("bash: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		i++;
	}
	return (1);
}
