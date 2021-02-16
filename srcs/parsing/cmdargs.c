#include "../../includes/minishell.h"

char	*args(char *whole_cmd, t_copy *copy, size_t i, t_redir *redir)// retrouver les arguments dans whole_cmd et mettre dans un char**
{
	int j;

	copy->args[i] = NULL;
	copy->j = -1;
	if (!(whole_cmd))
		return (NULL);
	if (!(copy->args[i] = malloc(sizeof(char) * (strlen(whole_cmd) + 1))))
		return (NULL);
	while (whole_cmd[copy->i] && whole_cmd[copy->i] == ' ')
		copy->i++;
	copy->i--;
	copy->args[i][0] = 0;
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != ' ')
	{
		j = 0;
		if ((whole_cmd[copy->i] == '1' || whole_cmd[copy->i] == '2') && whole_cmd[copy->i + 1] == '>' && whole_cmd[copy->i - 1] == ' ')
			copy->i++;
		while (whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '"')
		{
			while (whole_cmd[copy->i] == '"')
				if ((double_quote_arg(whole_cmd, copy, i)) == -1)
					return (NULL);
			while (whole_cmd[copy->i] == '\'')
				if ((simple_quote_arg(whole_cmd, copy, i)) == -1)
					return (NULL);
		}
		if (whole_cmd[copy->i] == '\\')
			copy->i++;
		if (whole_cmd[copy->i] && whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\')
		{
			if (whole_cmd[copy->i + 1] == '\\') // pour le cas du $\PATH
				copy->args[i][++copy->j] = whole_cmd[copy->i];
			else
				j = environnement(whole_cmd, copy, 1, i);
		}
		if ((whole_cmd[copy->i] == '>' || whole_cmd[copy->i] == '<') && whole_cmd[copy->i - 1] != '\\')
		{
			j = redirection(whole_cmd, copy, redir);
			if (j == -1)
				return (NULL);
		}
		if (whole_cmd[copy->i] == ' ' && copy->args[i][0])
			break;
/* AJOUT */
		if (whole_cmd[copy->i] != ' ' && j != 1 && ((whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] == '\\') || (whole_cmd[copy->i] != '$')))
			copy->args[i][++copy->j] = whole_cmd[copy->i];
/* AJOUT */
	}
	copy->args[i][copy->j + 1] = 0;
	return (copy->args[i]);
}

int		options(char *whole_cmd, t_copy *copy, t_redir *redir)
{
	char	**tmp;
	char	*arg;
	size_t	i;
	size_t	j;
	
	if (!(copy->args = (char **)malloc(sizeof(char *) * 1)))
		return (-1); 
	copy->args[0] = ft_strdup(copy->cmd);
	i = 1;
	while (1)
	{
		tmp = copy->args;
		if (!(copy->args = (char **)malloc(sizeof(char *) * (i + 1))))
			return (-1);
		j = i;
		while (j)
		{
			copy->args[j - 1] = ft_strdup(tmp[j - 1]);
			j--;
		}
		
		arg = args(whole_cmd, copy, i, redir);
		if (!arg || !arg[0])
			break;
		i++;
	}
	copy->args[i] = NULL;
	return (1);
}

void	init_redir_copy(t_copy *copy, t_redir *redir)
{
	copy->i = 0;
	copy->j = -1;
	copy->cmd = NULL;
	redir->sstdout = 1;
	redir->sstderr = 2;
	redir->sstdin = 1;
	redir->out1 = NULL;
	redir->out2 = NULL;
	redir->in = NULL;
}

/* AJOUT */
void	print_parsing(char **args, t_redir *redir)
{
	int i = 0;
	int j = 0;
	while (args[i])
	{
		printf("arg[%d] = %s\n", i, args[i]);
		i++;
	}
	if (redir->in)
	{
		printf("file stdin = %s\n", redir->in);
		printf("fd stdin = %d\n", redir->sstdin);
	}
	if (redir->out1)
	{
		printf("file stdout = %s\n", redir->out1);
		printf("fd stdout = %d\n", redir->sstdout);
		printf("fin du fichier ? = %d\n", redir->end);
	}
	if (redir->out2)
	{
		printf("file stderr = %s\n", redir->out2);
		printf("fd stderr = %d\n", redir->sstderr);
		printf("fin du fichier ? = %d\n", redir->end);
	}
}
/* AJOUT */

char	*cmd(char *whole_cmd, t_copy *copy, t_redir *redir) // retrouver la commande dans whole_cmd (peut etre une variable d'environnement)
{
	int j;
	init_redir_copy(copy, redir);
	if (!(whole_cmd))
		return (NULL);
	if (!(copy->cmd = malloc(sizeof(char) * (strlen(whole_cmd) + 1))))
		return (NULL);
	copy->cmd[0] = 0;
	while (whole_cmd[copy->i] && whole_cmd[copy->i] == ' ')
		copy->i++;
	while (whole_cmd[copy->i] && whole_cmd[copy->i] != ' ')
	{
		j = -2;
		//printf("passe à whole_cmd[copy->i] = %c\n", whole_cmd[copy->i]);
		//printf("copy->j = %d\n", copy->j);
		//printf("copy->cmd[0] = %c\n", copy->cmd[0]);
		if ((whole_cmd[copy->i] == '1' || whole_cmd[copy->i] == '2') && whole_cmd[copy->i + 1] == '>' && (!copy->cmd[0] || whole_cmd[copy->i - 1] == ' '))
			copy->i++;
		while (whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '"')
		{
			while (whole_cmd[copy->i] == '"')
				if ((double_quote(whole_cmd, copy)) == -1)
					return (NULL);
			while (whole_cmd[copy->i] == '\'')
				if ((simple_quote(whole_cmd, copy)) == -1)
					return (NULL);
		}
		if (whole_cmd[copy->i] == '\\')
			copy->i++;
		if (whole_cmd[copy->i] && whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\')
		{
			if (whole_cmd[copy->i + 1] == '\\')
				copy->cmd[++copy->j] = whole_cmd[copy->i];
			else
				j = environnement(whole_cmd, copy, 0, 0);
		}
		if ((whole_cmd[copy->i] == '>' || whole_cmd[copy->i] == '<') && whole_cmd[copy->i - 1] != '\\')
		{
			j = redirection(whole_cmd, copy, redir);
			if (j == -1)
				return (NULL);
		}
		//printf("copy->i = %d\n", copy->i);
		//printf("passe 2 à whole_cmd[copy->i] = %c\n", whole_cmd[copy->i]);
		if (whole_cmd[copy->i] == ' ' && copy->cmd[0])
			break;
/* AJOUT */
		if ((whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] == '\\') || (whole_cmd[copy->i] != '$' && j == -2))
			copy->cmd[++copy->j] = whole_cmd[copy->i];
		copy->i++;
/* AJOUT */
	}
	copy->cmd[copy->j + 1] = 0;
	options(whole_cmd, copy, redir);
/* AJOUT */
	//print_parsing(copy->args, redir);
/* AJOUT */
	return (copy->cmd);
}