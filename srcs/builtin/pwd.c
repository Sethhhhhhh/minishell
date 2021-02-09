#include "../../includes/minishell.h"

void	_pwd()
{
	ft_putstr_fd(get_env("PWD"), 1);
	ft_putchar_fd('\n', 1);
}