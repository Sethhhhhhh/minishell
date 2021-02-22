#include "../includes/minishell.h"

void	ft_exit()
{
	exit(0);
}

void	loop()
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
		i = -1;
		list = NULL;
		cmds = ft_minishell_split(line, ';');
		while (cmds[++i])
			list = add_cell(list, cmds[i], i);
		free(line);
		parse_pip(list);
		//print_list(list);
		minishell(list);
		prompt();
	}
	ft_putstr_fd("exit\n", 1);
	ft_exit();
}

void	loop_testeur(char *line)
{
	t_sep	*list;
	char	**cmds;
	size_t	i;

	i = -1;
	list = NULL;
	cmds = ft_minishell_split(line, ';');
	while (cmds[++i])
		list = add_cell(list, cmds[i], i);
	parse_pip(list);
	minishell(list);
}

void	prompt()
{
	char	pwd[4096 + 1];
	char	*user;
	size_t	len;
	size_t	count_slash;

	if ((user = get_env("USER")))
	{
		ft_putstr_fd("\033[32;1m", 1);
		ft_putstr_fd(user, 1);
		ft_putstr_fd("@\033[0m:", 1);
		free(user);
	}
	if (!getcwd(pwd, 4096))
	{
		ft_putstr_fd("$ ", 1);
		return;
	}
	len = ft_strlen(pwd);
	count_slash = 0;
	while (--len && count_slash < 3)
		if (pwd[len] == '/')
			count_slash++;
	ft_putstr_fd("\e[1;34m", 1);
	while (pwd[++len])
		ft_putchar_fd(pwd[len], 1);
	ft_putstr_fd("$\e[0m ", 1);
}

int	main(int ac, char **av, char **env)
{
	g_envs = env;
	if (ac >= 2)
	{
		if (av[1][0] == '-' && av[1][1] == 'c')
			loop_testeur(av[2]);
	}
	else
		loop();
	return (0);
}