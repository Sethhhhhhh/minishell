#include "../../includes/minishell.h"

void	init_redir(t_redir *redir)
{
	redir->sstdout = 1;
	redir->sstderr = 2;
	redir->sstdin = 1;
	redir->end = 0;
	redir->out1 = NULL;
	redir->out2 = NULL;
}

int		redir_out_error(char *whole_cmd, t_copy *copy, t_redir *redir) // retourner la char * de l'argument a mettre dans arg
{
	int i = -1;
	if (redir->end == 1)
		copy->i++;
	if (!(redir->out2 = malloc(sizeof(char) * strlen(whole_cmd) + 1)))
		return (-1);
	while (whole_cmd[copy->i] && whole_cmd[copy->i] == ' ')
		copy->i++;
	while (whole_cmd[copy->i] && whole_cmd[copy->i] != ' ') // recuperer le fichier derriere '>'
	{
		redir->out2[++i] = whole_cmd[copy->i]; // recuperer le fichier derriere '>'
		copy->i++;
	}
	redir->out2[i + 1] = 0;
	redir->sstderr = open(redir->out2, O_CREAT);
	printf("file stderr = %s\n", redir->out2);
	printf("fd stderr = %d\n", redir->sstderr);
	printf("fin du fichier ? = %d\n", redir->end);
	return (1);
}

int		redir_out(char *whole_cmd, t_copy *copy, t_redir *redir)
{
	int i = -1;
	int j = 0;

	copy->i++;
	if (whole_cmd[copy->i] == '>')
		redir->end = 1;
	if (whole_cmd[copy->i - 2] == '2' && whole_cmd[copy->i - 3] == ' ') // pour distinguer que c'est le stderr et pas par defaut stdout
		if ((j = (redir_out_error(whole_cmd, copy, redir))))
			return (j);
	if (redir->end == 1)
		copy->i++;
	if (!(redir->out1 = malloc(sizeof(char) * strlen(whole_cmd) + 1)))
		return (-1);
	while (whole_cmd[copy->i] && whole_cmd[copy->i] == ' ')
		copy->i++;
	while (whole_cmd[copy->i] && whole_cmd[copy->i] != ' ') // recuperer le fichier derriere '>'
	{
		redir->out1[++i] = whole_cmd[copy->i]; // recuperer le fichier derriere '>'
		copy->i++;
	}
	redir->out1[i + 1] = 0;
	redir->sstdout = open(redir->out1, O_CREAT);
	printf("file stdout = %s\n", redir->out1);
	printf("fd stdout = %d\n", redir->sstdout);
	printf("fin du fichier ? = %d\n", redir->end);
	return (1);
}

int		redir_in(char *whole_cmd, t_copy *copy, t_redir *redir)
{
	
}

int		redir(char *whole_cmd, t_copy *copy)
{
	t_redir redir;
	int i;
	init_redir(&redir);
	if (whole_cmd[copy->i] == '>')
		i = redir_out(whole_cmd, copy, &redir);
	if (whole_cmd[copy->i] == '<')
		i = redir_in(whole_cmd, copy, &redir);
	return (i);
}