#include "../../includes/minishell.h"

char	*args(char *whole_cmd, t_copy *copy, size_t i)// retrouver les arguments dans whole_cmd et mettre dans un char**
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
			if (redir(whole_cmd, copy) == -1)
				return (NULL);
		if (whole_cmd[copy->i] == ' ' && copy->args[i][0])
			break;
		if (whole_cmd[copy->i] != ' ')
			copy->args[i][++copy->j] = whole_cmd[copy->i];
	}
	copy->args[i][copy->j + 1] = 0;
	return (copy->args[i]);
}

int		options(char *whole_cmd, t_copy *copy)
{
	char	**tmp;
	char	*arg;
	size_t	i;
	size_t	j;
	copy->args = NULL;

	i = 0;
	if (!(whole_cmd[copy->i]))
		return (-1);
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
		arg = args(whole_cmd, copy, i);
		if (!arg || !arg[0])
			break;
		printf("arg[%zu] = %s\n", i, copy->args[i]);
		i++;
	}
	copy->args[i] = NULL;
	printf("arg[%zu] = %s\n", i, copy->args[i]);
	return (1);
}

char	*cmd(char *whole_cmd) // retrouver la commande dans whole_cmd (peut etre une variable d'environnement)
{
	t_copy copy;
	copy.i = 0;
	copy.j = -1;
	copy.cmd = NULL;

	if (!(whole_cmd))
		return (NULL);
	if (!(copy.cmd = malloc(sizeof(char) * (strlen(whole_cmd) + 1))))
		return (NULL);
	copy.cmd[0] = 0;
	while (whole_cmd[copy.i] && whole_cmd[copy.i] == ' ')
		copy.i++;
	while (whole_cmd[copy.i] && whole_cmd[copy.i] != ' ')
	{
		if (whole_cmd[copy.i] == '\'' || whole_cmd[copy.i] == '"')
		{
			while (whole_cmd[copy.i] == '"')
				if ((double_quote(whole_cmd, &copy)) == -1)
					return (NULL);
			while (whole_cmd[copy.i] == '\'')
				if ((simple_quote(whole_cmd, &copy)) == -1)
					return (NULL);
		}
		if (whole_cmd[copy.i] == '\\')
			copy.i++;
		if (whole_cmd[copy.i] == ' ' && copy.cmd[0])
			break;
		copy.cmd[++copy.j] = whole_cmd[copy.i];
		copy.i++;
	}
	copy.cmd[copy.j + 1] = 0;
	printf("cmd = %s\n", copy.cmd);
	options(whole_cmd, &copy);
	return (copy.cmd);
}
