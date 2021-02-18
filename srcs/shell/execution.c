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
			//print_parsing(cmdarg.args, &redir);
//			printf("---------\n");
			execution(&cmdarg, &redir);
		}
		list = list->next;
		i++;
	}
}

void	redir_dup(t_copy *cmdarg, t_redir *redir)
{
	int		savein;
	int		saveout1;
	int		saveout2;

	if (redir->in)
	{
		savein = dup(0);
		close(0);
		dup2(redir->sstdin, 0);
	}
	if (redir->out1)
	{
		saveout1 = dup(1);
		close (1);
		dup2(redir->sstdout, 1);
	}
	if (redir->out2)
	{
		saveout2 = dup(2);
		close (2);
		dup2(redir->sstderr, 2);
	}
	exec(cmdarg->args);
	if (redir->in)
		dup2(savein, 0);
	if (redir->out1)
		dup2(saveout1, 1);
	if (redir->out2)
		dup2(saveout2, 2);
	//write(1, "coucou", 7); // pour tester avec stdout : ca s'ecrira dans fddest
}

void	execution(t_copy *cmdarg, t_redir *redir)
{
	if (redir->in || redir->out1 || redir->out2)
		redir_dup(cmdarg, redir);
	else
		exec(cmdarg->args);	
}