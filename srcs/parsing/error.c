#include "../../includes/minishell.h"

void	ft_error_exit(int errno, char *msg)
{
	printf("%s\n", msg);
	exit (0);
}