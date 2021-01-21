#include "../../includes/minishell.h"

t_sep	*create_cell(char *cmd_sep)
{
	t_sep	*cell;

	if (!(cell = malloc(sizeof(t_sep))))
		return (NULL);
	cell->prev = NULL;
	cell->next = NULL;
	cell->pipcell = NULL;
	cell->cmd_sep = cmd_sep;
	return(cell);
}

t_sep	*add_cell(t_sep *list, char *cmd_sep, int pos) //list ici n'est que la première cellule de la liste
{
	t_sep *prec;
	t_sep *cur = list; //la celule qu'on est en train de parcourir
	int i = 0;
	t_sep *cell = create_cell(cmd_sep);
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

void	print_list(t_sep *list)
{
	int i = 0;
	while (list)
	{
		printf("-----------------------------------\n");
		printf("| i = %d                            \n", i);
		printf("| list->cmd_sep : %s            \n", list->cmd_sep);
		if (list->pipcell != NULL)
			print_pip_list(list->pipcell);
		printf("-----------------------------------\n");
		list = list->next;
		i++;
	}
}

t_sep	*parse_sep()
{
	t_sep	*list = NULL;
	char	*line;
	char	**cmds;
	int		i;

	list = NULL;
	i = -1;
	if (get_next_line(0, &line))
	{
		cmds = ft_split(line, ';');
		while (cmds[++i])
			list = add_cell(list, cmds[i], i);
		free(line);
	}
	return (list);
}