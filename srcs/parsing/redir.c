#include "../../includes/minishell.h"

void	create_file(t_redir *redir, int type)
{
	if (type == 1)
	{
		if (redir->end == 1)
			redir->sstdout = open(redir->out1, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			redir->sstdout = open(redir->out1, O_CREAT | O_RDWR | O_TRUNC, 0644);
		//if (!redir->sstdout)
		//	ft_error(errno, "erreur");
	}
	if (type == 0)
	{
		redir->sstdin = open(redir->in, O_RDONLY);
		//printf("%d\n", errno);
		//if (redir->sstdin == -1)
		//	ft_error_exit(errno, "No such file or Directory");
	}
	if (type == 2)
	{
		if (redir->end == 1)
			redir->sstderr = open(redir->out1, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			redir->sstderr = open(redir->out2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
}

int		redir_out_error(char *whole_cmd, t_copy *copy, t_redir *redir) // redirection de stderr : recuperer out2, et le fd sstderr
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
		if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\')
			environnement_redir(whole_cmd, copy, 2, redir);
		while (whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '"')
		{
			while (whole_cmd[copy->i] == '"')
				if ((double_quote_redir(whole_cmd, copy, redir, redir->out2, 2)) == -1)
				{
					create_file(redir, 2);
					return (4);
				}
			while (whole_cmd[copy->i] == '\'')
				if ((simple_quote_redir(whole_cmd, copy, i, redir, redir->out2)) == -1)
				{
					create_file(redir, 2);
					return (4);
				}
		}
/*AJOUT*/
		if (whole_cmd[copy->i] == '\\')
			copy->i++;
/*AJOUT*/
		if ((whole_cmd[copy->i] == '<' || whole_cmd[copy->i] == '>') && (whole_cmd[copy->i - 1] != '\\')) //dans le cas ou y a plusieurs redirections : echo mdr >hey>hey2
		{
			copy->i--;
			break;
		}
		redir->out2[++redir->i] = whole_cmd[copy->i]; // recuperer le fichier derriere '>'git
		copy->i++;
	}
	redir->out2[redir->i + 1] = 0;
	create_file(redir, 2);
	return (1);
}

int		redir_out(char *whole_cmd, t_copy *copy, t_redir *redir) // redirection de stdout : recuperer out1, et le fd sstdout
{
	int i = -1;
	int j = 0;

	copy->i++;
	if (whole_cmd[copy->i] == '>')
		redir->end = 1;
	if (whole_cmd[copy->i - 2] == '2' && (whole_cmd[copy->i - 3] == ' ' || copy->i == 2)) // pour distinguer que c'est le stderr ou pas (par defaut stdout)
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
		if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\')
			environnement_redir(whole_cmd, copy, 1, redir);
		while (whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '"')
		{
			while (whole_cmd[copy->i] == '"')
				if ((double_quote_redir(whole_cmd, copy, redir, redir->out1, 1)) == -1)
				{
					create_file(redir, 1);
					return (4);
				}
			while (whole_cmd[copy->i] == '\'')
				if ((simple_quote_redir(whole_cmd, copy, i, redir, redir->out1)) == -1)
				{
					create_file(redir, 1);
					return (4);
				}
		}
/*AJOUT*/
		if (whole_cmd[copy->i] == '\\')
			copy->i++;
/*AJOUT*/
		if ((whole_cmd[copy->i] == '<' || whole_cmd[copy->i] == '>') && (whole_cmd[copy->i - 1] != '\\')) //dans le cas ou y a plusieurs redirections : echo mdr >hey>hey2
		{
			copy->i--;
			break;
		}
		redir->out1[++redir->i] = whole_cmd[copy->i]; // recuperer le fichier derriere '>'
		copy->i++;
	}
	redir->out1[redir->i + 1] = 0;
	create_file(redir, 1);
	//printf("file stdout = %s\n", redir->out1);
	//printf("fd stdout = %d\n", redir->sstdout);
	//printf("fin du fichier ? = %d\n", redir->end);
	return (1);
}

int		redir_in(char *whole_cmd, t_copy *copy, t_redir *redir) // redirection de stdin : recuperer in et le fd sstdin
{
	int i = -1;
	int j = 0;

	copy->i++;
	if (!(redir->in = malloc(sizeof(char) * strlen(whole_cmd) + 1)))
		return (-1);
	//if (whole_cmd[copy->i] == '>')
	//	printf("special case\n");
	while (whole_cmd[copy->i] && whole_cmd[copy->i] == ' ')
		copy->i++;
	while (whole_cmd[copy->i] && whole_cmd[copy->i] != ' ') // recuperer le fichier derriere '>'
	{
		if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\')
			environnement_redir(whole_cmd, copy, 0, redir);
		while (whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '"')
		{
			while (whole_cmd[copy->i] == '"')
				if ((double_quote_redir(whole_cmd, copy, redir, redir->in, 0)) == -1)
				{
					create_file(redir, 0);
					return (4);
				}
			while (whole_cmd[copy->i] == '\'')
				if ((simple_quote_redir(whole_cmd, copy, i, redir, redir->in)) == -1)
				{
					create_file(redir, 0);			
					return (4);
				}
		}
/*AJOUT*/
		if (whole_cmd[copy->i] == '\\')
			copy->i++;
/*AJOUT*/
		if ((whole_cmd[copy->i] == '<' || whole_cmd[copy->i] == '>') && (whole_cmd[copy->i - 1] != '\\')) //dans le cas ou y a plusieurs redirections : echo mdr <hey<hey2
		{
			copy->i--;
			break;
		}
		redir->in[++redir->i] = whole_cmd[copy->i]; // recuperer le fichier derriere '>'
		copy->i++;
	}
	redir->in[redir->i + 1] = 0;
	create_file(redir, 0);
	//printf("file stdin = %s\n", redir->in);
	//printf("fd stdin = %d\n", redir->sstdin);
	return (1);
}

int		redirection(char *whole_cmd, t_copy *copy, t_redir *redir)
{
	int i;

	redir->i = -1; //dans le cas ou y a plusieurs redirections : echo mdr >hey >hey2
	if (whole_cmd[copy->i] == '>')
	{
		redir->end = 0;//dans le cas ou y a plusieurs redirections : echo mdr >hey >hey2
		i = redir_out(whole_cmd, copy, redir);
	}
	if (whole_cmd[copy->i] == '<')
		i = redir_in(whole_cmd, copy, redir);
	return (i);
}