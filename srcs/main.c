#include "../includes/minishell.h"

char	**get_path(t_env *tenv)
{
	int		i;
	int		path_index;

	i = 0;
	path_index = -1;
	while (tenv->env[i])
	{
		if (!ft_strncmp(tenv->env[i], "PATH=", 5)) //check si les 5 premiers caractères de tenv->env[i] est = à "PATH="
		{
			path_index = i;
			break;
		}
		i++;
	}
	if (path_index >= 0)
	{
		tenv->paths = ft_split(tenv->env[path_index], ':');
		tenv->paths[0] = ft_substr(tenv->paths[0], 5, ft_strlen(tenv->paths[0])); //enlever PATH= de tenv->paths[0]
		return (tenv->paths);
	}	
	return (NULL);
}

void	loop(t_env *tenv)
{
	t_sep *list;

	while (1)
	{
		write(0, "~$ ", 3); //pour le prompt
		list = parse_sep();
		print_list(list);
		minishell(list);
	}
}

int	main(int ac, char **av, char **env)
{
	int i = -1;
	t_env tenv;
	tenv.env = env;
	g_envs = env;

	if (!get_path(&tenv))
		return (0);
	loop(&tenv);
	return (0);
	//ft_pipe("coucou");
	//sys_call("ls", paths, NULL, env);
	//sys_call("coucou", paths, "-l", env);
	//sys_call("pwd", paths, NULL, env);*/
}
