/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:29:42 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/13 15:09:52 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_directory(char *path)
{
	struct stat	st;
	char		pwd[4096 + 1];

	getcwd(pwd, 4096);
	if (!chdir(path))
	{
		set_env("OLDPWD", pwd);
		set_env("PWD", getcwd(NULL, 0));
		free(path);
		return (1);
	}
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	g_status = 1;
	if (stat(path, &st) == -1)
	{
		ft_putstr_fd(": No such file or directory", 2);
		g_status = 127;
	}
	else if (!(st.st_mode & S_IXUSR))
		ft_putstr_fd(": Permission denied", 2);
	else
		ft_putstr_fd(": Not a directory", 2);
	ft_putchar_fd('\n', 2);
	free(path);
	return (1);
}

int	s_path(char **args, char *home)
{
	char *tmp;

	if (!args[1][0])
	{
		free(home);
		return (set_directory("."));
	}
	if (!ft_strcmp(args[1], "-"))
	{
		free(home);
		set_directory(get_env("OLDPWD"));
		tmp = get_env("PWD");
		ft_putstr_fd(tmp, 1);
		free(tmp);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if (!ft_strcmp(args[1], "--"))
		return (set_directory(home));
	else
		return (set_directory(args[1]));
	return (0);
}

int	run_cd(char **args)
{
	char	*home;

	g_status = 0;
	if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!args[1] || ft_strequ(args[1], "~"))
	{
		if (!(home = get_env("HOME")))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		return (set_directory(home));
	}
	return (s_path(args, home));
}
