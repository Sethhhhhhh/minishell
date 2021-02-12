#include "../../includes/minishell.h"

static int	_set(char *path)
{
	struct stat st;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		set_env("OLDPWD", pwd);
		set_env("PWD", getcwd(NULL, 0));
		return (1);
	}
	ft_putstr_fd("cd: ", 2);
	if (!stat(path, &st))
	{
		ft_putstr_fd("no such file or directory: ", 2);
		return (0);
	}
	else if (!(st.st_mode & S_IXUSR))
		ft_putstr_fd("permission denied: ", 2);
	else
		ft_putstr_fd("not a directory: ", 2);
	ft_putstr_fd(path, 2);
	ft_putchar_fd('\n', 2);
	return (0);
}

int			run_cd(char **args)
{
	char	*home;

	home = get_env("HOME");
	if (!args[1])
		return (_set(home));
	if (!ft_strcmp(args[1], "-"))
	{
		_set(get_env("OLDPWD"));
		ft_putstr_fd(get_env("PWD"), 1);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if (!ft_strcmp(args[1], "--"))
		return (_set(home));
	else
		return (_set(args[1]));
	return (0);
}
