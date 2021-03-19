#include "../includes/minishell.h"

void	ft_exit(t_copy *copy)
{
	free_cmdarg(copy);
	ft_free_array(g_envs);
	if (copy->list)
		free_list(copy->list);
	if (copy->cmdssep)
		free(copy->cmdssep);
	if (!g_tester)
		ft_putstr_fd("exit\n", 2);
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
	return (1);
}

void	loop()
{
	t_copy	cmdarg;
	char	*line;
	char	*tmp;
	size_t	i;

	tmp = get_env("SHLVL");
	i = (ft_atoi(tmp) + 1);
	free(tmp);
	tmp = ft_itoa(i);
	signal(SIGQUIT, sigint_handler);
	signal(SIGINT, sigint_handler);
	set_env("SHLVL", tmp);
	free(tmp);
	line = NULL;
	prompt();
	g_pid = 0;
	g_tester = 0;
	while (get_next_line(0, &line) > 0)
	{
		signal(SIGINT, sigint_handler);
		if (_check_space_colon(line))
		{
			free(line);
			prompt();
			continue;
		}
		cmdarg.list = NULL;
		cmdarg.cmdssep = NULL;
		i = -1;
		if (syntax_error(line, '|') != -1 && syntax_error(line, ';') != -1)
		{
			cmdarg.cmdssep = ft_minishell_split(line, ';');
			free(line);
			while (cmdarg.cmdssep[++i])
				cmdarg.list = add_cell(cmdarg.list, cmdarg.cmdssep[i], i);
			parse_pip(cmdarg.list);
			minishell(cmdarg.list, &cmdarg);
		}
		else
			free(line);
		prompt();
	}
	ft_exit(&cmdarg);
}

void	loop_testeur(char *line)
{
	t_sep	*list;
	t_copy	cmdarg;
	char	**cmds;
	size_t	i;

	if (_check_space_colon(line))
		return;
	list = NULL;
	i = -1;
	g_tester = 1;
	if (syntax_error(line, '|') != -1 && syntax_error(line, ';') != -1)
	{
		cmds = ft_minishell_split(line, ';');
		while (cmds[++i])
			list = add_cell(list, cmds[i], i);
		parse_pip(list);
		minishell(list, &cmdarg);
		free_list(list);
		if (cmds)
			free(cmds);
	}
	ft_exit(&cmdarg);
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
	size_t  i;  

    i = 0;
    while (env[i])
        i++;
    if (!(g_envs = (char **)malloc(sizeof(char *) * (i + 1))))
        return (0);
    i = 0;
    while (env[i])
    {   
        g_envs[i] = ft_strdup(env[i]);
        i++;
    }   
    g_envs[i] = 0;
	if (ac >= 2)
	{
		if (av[1][0] == '-' && av[1][1] == 'c' && av[2])
			loop_testeur(av[2]);
		else
			return_error(av[1], ": No such file or directory\n", 0, 127);
	}
	else
		loop();
	return (0);
}
