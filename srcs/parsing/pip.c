#include "../../includes/minishell.h"

t_pip	*create_pip_cell(char *cmd_pip)
{
	t_pip   *cell;

	if (!(cell = malloc(sizeof(t_pip))))
		return (NULL);
	cell->prev = NULL;
	cell->next = NULL;
	cell->cmd_pip = cmd_pip;
	return(cell);
}

t_pip   *add_pip_cell(t_pip *list, char *cmd_pip, int pos)
{
	t_pip *prec;
	t_pip *cur = list; //la celule qu'on est en train de parcourir
	int i = 0;
	t_pip *cell = create_pip_cell(cmd_pip);
	if (list == NULL)
		return (cell);
	while (i < pos)
	{
		i++;
		prec = cur;
		cur = cur->next;
	}
	prec->next = cell;
	cell->next = cur;
	return (list);
}

void	print_pip_list(t_pip *piplist)
{
	int i = 0;
	while (piplist)
	{
		printf("| piplist->cmd_pip : %s            \n", piplist->cmd_pip);
		piplist = piplist->next;
		i++;
	}
}

int		pipeinstr(char c, char *str)
{
	char quote;
	int i = -1;
	while (str[++i])
	{
		while (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
            while (str[i] && str[++i] != quote)
			{
				if (str[i] == '\\')
					i++;
			}
			i++;
		}
		if (str[i] == '\\')
			i++;
		if (str[i] == c && str[i - 1] != '\\')
			return (i);
	}
	return (-1);
}

void    parse_pip(t_sep *list)
{
	char	**cmds;
	t_sep   *prec;
	t_sep   *cur = list; //la celule qu'on est en train de parcourir
	int     j = -1;

	while (cur)
	{
		if ((pipeinstr('|', cur->cmd_sep)) > -1)
		{
			cmds = ft_minishell_split(cur->cmd_sep, '|');
			while (cmds[++j])
				cur->pipcell = add_pip_cell(cur->pipcell, cmds[j], j);
		}
		prec = cur;
		cur = cur->next;
	}
}