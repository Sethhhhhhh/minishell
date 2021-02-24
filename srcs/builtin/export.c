#include "../../includes/minishell.h"

static size_t	_len_without_extra_spaces(char *str)
{	
	size_t	i;
	size_t	len;
	char	found_space;

	len = ft_strlen(str);
	while (str[len - 1] && ft_isspace(str[len - 1]))
		len--;
	str[len] = '\0';
	i = 0; 
	while (str[i] && ft_isspace(str[i]))
		i++;
	len -= i;
	i--;
	found_space = 0;
	while (str[++i])
		if (ft_isspace(str[i]) && !found_space)
			found_space = 1;
		else if (ft_isspace(str[i]))
			len--;
		else
			found_space = 0;
	return (len);
}

static char	*_strip_extra_spaces(char *str)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;
	
	len = _len_without_extra_spaces(str);
	if (!(new = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	k = ft_strlen(str);
	while (str[k - 1] && ft_isspace(str[k - 1]))
		k--;
	str[k] = '\0';
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	k = 0;
	j = 0;
	while (str[i])
	{
		if ((ft_isspace(str[i]) && !k && (k = 1)))
			new[j++] = str[i];
		else if (!ft_isspace(str[i]) && !(k = 0))
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

int	run_export(char **args)
{
	char	*strip;
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
			set_env(ft_substr(g_envs[index], 0, ft_get_char_by_index(g_envs[index], '=')),
				_strip_extra_spaces(ft_substr(args[i], ft_get_char_by_index(args[i], '=') + 1, ft_strlen(args[i]))));
		else
		{
			count = get_envs_count() + 1;
			g_envs = realloc_envs(count);
			g_envs[count - 1] =	ft_strjoin(
				ft_substr(args[i], 0, ft_get_char_by_index(args[i], '=') + 1),
				_strip_extra_spaces(ft_substr(args[i], ft_get_char_by_index(args[i], '=') + 1, ft_strlen(args[i]))
			));
		}
		i++;
	}
	return (1);
}
