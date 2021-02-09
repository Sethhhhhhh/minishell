#include "../../includes/minishell.h"

void	_export(char **args)
{
	size_t	i;
	ssize_t	index;
	size_t	equal_index;
	size_t	count;

	if (!args[1])
	{
		ft_putstr_fd("export: too few arguments.", 1);
		ft_putchar_fd('\n', 1);
	}
	i = 1;
	while (args[i])
	{
		equal_index = ft_get_char_by_index(args[i], '=');	
		if ((index = find_env(ft_substr(args[i], 0, equal_index))) != -1)
		{
			set_env(
				ft_substr(g_envs[index], 0, ft_get_char_by_index(g_envs[index], '=')),
				ft_substr(args[i], (equal_index + 1), ft_strlen(args[i]))
			);
		}
		else
		{
			count = get_envs_count() + 1;
			g_envs = realloc_envs(count);
			g_envs[count - 1] = ft_strdup(args[i]);				
		}
		i++;
	}
}