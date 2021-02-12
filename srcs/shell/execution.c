#include "../../includes/minishell.h"

void	minishell(t_sep *list)
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
				printf("---------\n");
				execution(&cmdarg, &redir);
				list->pipcell = list->pipcell->next;
			}
		}
		else
		{
			cmd(list->cmd_sep, &cmdarg, &redir);
//			printf("---------\n");
			execution(&cmdarg, &redir);
		}
		list = list->next;
		i++;
	}
}

void	redir_dup(int fdsrc, int fddest)
{
	int		save;

	save = dup(fdsrc);
	close (fdsrc);
	dup2(fddest, fdsrc); //fd src redirige vers le fd dest
	//write(1, "coucou", 7); // pour tester avec stdout : ca s'ecrira dans fddest
	dup2(save, fdsrc); // redirection enlevee
	//write(1, "ok", 3); // pour tester avec stdout : s'ecrira bien sur le stdout
}

void	execution(t_copy *cmdarg, t_redir *redir)
{	
	if (redir->in)
		redir_dup(0, redir->sstdin);
	if (redir->out1)
		redir_dup(1, redir->sstdout);
	if (redir->out2)
		redir_dup(2, redir->sstderr);
	g_fork = 0;
	exec(cmdarg->args);
}
