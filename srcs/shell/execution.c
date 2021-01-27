#include "../../includes/minishell.h"

void	execution(t_sep *list)
{
	t_copy cmdarg;
	t_redir redir;

	int i = 0;
	while (list)
	{
		if (list->pipcell != NULL)
		{
			while (list->pipcell)
			{
				cmd(list->pipcell->cmd_pip, &cmdarg, &redir);
				printf("\n");
				list->pipcell = list->pipcell->next;
			}
		}
		else
		{
			printf("%s\n", list->cmd_sep);
			cmd(list->cmd_sep, &cmdarg, &redir);
			printf("\n");
		}
		list = list->next;
		i++;
	}
}
