#include "../../includes/minishell.h"

void	sigint_handler(int sign_num)
{
	printf("%d\n", sign_num);
	if ((sign_num == SIGINT || sign_num == SIGQUIT) && g_fork != 0)
	{
		if (!kill(g_fork, sign_num))
		{
			if (sign_num == SIGQUIT)
				ft_putstr_fd("Quit: 3\n", 1);
			else if (sign_num == SIGINT)
				ft_putchar_fd('\n', 1);
		}
		else if (sign_num == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			prompt();
		}
	}
	else
		if (sign_num == SIGINT)
			prompt();
}
