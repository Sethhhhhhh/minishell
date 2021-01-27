#include "../../includes/minishell.h"

char	*args(char *whole_cmd, t_copy *copy, size_t i, t_redir *redir)// retrouver les arguments dans whole_cmd et mettre dans un char**
{
	copy->args[i] = NULL;
	copy->j = -1;

	if (!(whole_cmd))
		return (NULL);
	if (!(copy->args[i] = malloc(sizeof(char) * (strlen(whole_cmd) + 1))))
		return (NULL);
	if (i == 0)
	{
		copy->args[i] = ft_strdup(copy->cmd);
		return (copy->args[i]);
	}
	while (whole_cmd[copy->i] && whole_cmd[copy->i] == ' ')
		copy->i++;
	copy->i--;
	copy->args[i][0] = 0;
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != ' ')
	{
		if ((whole_cmd[copy->i] == '1' || whole_cmd[copy->i] == '2') && whole_cmd[copy->i + 1] == '>' && whole_cmd[copy->i - 1] == ' ')
			copy->i++;
		if (whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '"')
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
		if ((whole_cmd[copy->i] == '>' || whole_cmd[copy->i] == '<') && whole_cmd[copy->i - 1] != '\\')
			if (redirection(whole_cmd, copy, redir) == -1)
				return (NULL);
		if (whole_cmd[copy->i] == ' ' && copy->args[i][0])
			break;
		if (whole_cmd[copy->i] != ' ')
			copy->args[i][++copy->j] = whole_cmd[copy->i];
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
	copy->args = NULL;


	i = 0;
	while (1)
	{
		if (i > 0)
			tmp = copy->args;
		if (!(copy->args = (char **)malloc(sizeof(char *) * (i + 1))))
			return (-1);
		if (i > 0)
		{
			j = i - 1;
			while (j)
			{
				copy->args[j] = ft_strdup(tmp[j]);
				j--;
			}
			while (j < i)
			{
				//free(tmp[j]);
				j++;
			}
		}
		arg = args(whole_cmd, copy, i, redir);
		if (!arg || !arg[0])
		{
			break;
		}
		printf("arg[%zu] = %s\n", i, copy->args[i]);
		i++;
	}
	copy->args[i] = NULL;
	printf("arg[%zu] = %s\n", i, copy->args[i]);
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
	redir->end = 0;
	redir->out1 = NULL;
	redir->out2 = NULL;
	redir->in = NULL;
	redir->i = -1;
}

char	*cmd(char *whole_cmd, t_copy *copy, t_redir *redir) // retrouver la commande dans whole_cmd (peut etre une variable d'environnement)
{
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
		if (whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '"')
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
		if (whole_cmd[copy->i] == ' ' && copy->cmd[0])
			break;
		copy->cmd[++copy->j] = whole_cmd[copy->i];
		copy->i++;
	}
	copy->cmd[copy->j + 1] = 0;
	options(whole_cmd, copy, redir);
	return (copy->cmd);
}
