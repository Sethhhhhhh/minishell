#include "../includes/minishell.h"

void	ft_exit()
{
	ft_free_array(g_envs);
	exit(g_status);
}

int		return_error(char *cmd, char *msg, int ret, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	if (status >= 0)
		g_status = status;
	return (ret);
}

static int	_check_space_colon(char *line)
{
	size_t	i;
	int		colon;

	colon = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == ':' && colon) || (!ft_isspace(line[i]) && line[i] != ':'))
			return (0);
		if (line[i] == ':')
			colon = 1;
		i++;
	}
	prompt();
	return (1);
}

void	loop()
{
	t_sep	*list;
	char	*line;
	char	**cmds;
	char	*tmp;
	size_t	i;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);

	tmp = get_env("SHLVL");
	i = (ft_atoi(tmp) + 1);
	free(tmp);
	tmp = ft_itoa(i);
	set_env("SHLVL", tmp);
	line = NULL;
	prompt();
	while (get_next_line(0, &line) > 0)
	{
		if (_check_space_colon(line))
			continue;
		list = NULL;
		cmds = NULL;
		i = -1;
		if (syntax_error(line, '|') != -1 && syntax_error(line, ';') != -1)
		{
			cmds = ft_minishell_split(line, ';');
			free(line);
			while (cmds[++i])
				list = add_cell(list, cmds[i], i);
			parse_pip(list);
			minishell(list);
			free_list(list);
			if (cmds)
				free(cmds);
		}
		else
			free(line);
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

	if (_check_space_colon(line))
		return;
	list = NULL;
	i = -1;
	if (syntax_error(line, '|') != -1 && syntax_error(line, ';') != -1)
	{
		cmds = ft_minishell_split(line, ';');
		while (cmds[++i])
			list = add_cell(list, cmds[i], i);
		parse_pip(list);
		minishell(list);
		ft_free_array(cmds);
	}
	ft_exit();
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
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	if (!(g_envs = malloc(sizeof(char *) * (i + 1))))
		return (0);
	g_envs[i] = NULL;
	i = 0;
	while (env[i])
	{
		g_envs[i] = ft_strdup(env[i]);
		i++;
	}
	if (ac >= 2)
	{
		if (av[1][0] == '-' && av[1][1] == 'c')
			loop_testeur(av[2]);
		else
			return_error(av[1], ": No such file or directory\n", 0, 127);
	}
	else
		loop();
	return (0);
}
