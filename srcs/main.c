#include "../includes/minishell.h"

void	ft_exit()
{
	exit(0);
}

void	loop(t_env *tenv)
{
	t_sep	*list;
	char	*line;
	char	**cmds;
	size_t	i;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	prompt();
	while (get_next_line(0, &line) > 0)
	{
		i = 0;
		list = NULL;
		cmds = ft_split(line, ';');
		while (cmds[i])
		{
			list = add_cell(list, cmds[i], i);
			i++;
		}
		free(line);
		parse_pip(list);
		//print_list(list);
		minishell(list);
		prompt();
	}
	ft_putstr_fd("exit\n", 1);
	ft_exit();
}

void	prompt()
{
	ft_putstr_fd(get_env("PWD"), 1);
	ft_putstr_fd("$ ", 1);
}

int	main(int ac, char **av, char **env)
{
	t_env tenv;

	tenv.env = env;
	g_envs = env;
	loop(&tenv);
	return (0);
}
