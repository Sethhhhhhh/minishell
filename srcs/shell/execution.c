#include "../../includes/minishell.h"

void	execution(t_sep *list)
{
	int i = 0;
	while (list)
	{
		if (list->pipcell != NULL)
		{
			while (list->pipcell)
			{
				cmd(list->pipcell->cmd_pip);
				list->pipcell = list->pipcell->next;
			}
		}
		else
			cmd(list->cmd_sep);
		list = list->next;
		i++;
	}
}
