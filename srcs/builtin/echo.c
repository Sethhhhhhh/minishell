#include "../../includes/minishell.h"

void	_echo(char **args)
{
	size_t	i;
	int		n;

	n = 0;
	i = 1;
	if (!args[1])
		ft_putchar_fd('\n', 1);
	if (!strcmp(args[1], "-n") && ++i)
		n = 1;
	while (args[i])
	{
		if ((i > 1 && !n) || (i > 2 && n))
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(args[i], 1);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', 1);
}