/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:53:21 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/13 12:54:45 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		cmd_quoting(t_copy *copy, int j)
{
	while (copy->wc[copy->i] == '\'' || copy->wc[copy->i] == '"')
	{
		while (copy->wc[copy->i] == '"')
		{
			j = d_quote(copy, j);
			if (j == -1)
				return (-1);
		}
		while (copy->wc[copy->i] == '\'')
		{
			j = s_quote(copy);
			if (j == -1)
				return (-1);
		}
	}
	if (copy->wc[copy->i] == '\\')
		copy->i++;
	return (j);
}

int		cmd_redir_env(t_copy *copy, int j)
{
	if (copy->wc[copy->i] && copy->wc[copy->i] == '$'
		&& copy->wc[copy->i - 1] != '\\')
	{
		if (copy->wc[copy->i + 1] == '\\')
			copy->cmd[++copy->j] = copy->wc[copy->i];
		else
			j = env(copy, 0, 0, 1);
	}
	if ((copy->wc[copy->i] == '>' || copy->wc[copy->i] == '<')
		&& copy->wc[copy->i - 1] != '\\')
		j = redirection(copy);
	return (j);
}

char	*cmd(t_copy *copy)
{
	int		j;

	while (copy->wc[copy->i] && copy->wc[copy->i] != ' ')
	{
		j = -2;
		if ((copy->wc[copy->i] == '1' || copy->wc[copy->i] == '2')
			&& copy->wc[copy->i + 1] == '>'
			&& (!copy->cmd[0] || copy->wc[copy->i - 1] == ' '))
			copy->i++;
		j = cmd_quoting(copy, j);
		j = cmd_redir_env(copy, j);
		if ((copy->wc[copy->i] == ' ' && copy->wc[copy->i - 1] != '\\')
			&& (copy->cmd[0] || (!copy->cmd[0] && (copy->wc[copy->i - 1] == '"'
						|| copy->wc[copy->i - 1] == '\'') && (copy->wc
						[copy->i - 2] == '"' || copy->wc[copy->i - 2] == '\''
						|| j == 1))))
			break ;
		if (copy->i < (int)ft_strlen(copy->wc) && ((copy->wc[copy->i] == '$'
					&& copy->wc[copy->i - 1] == '\\') || (copy->wc[copy->i]
					!= '$' && j == -2)))
			copy->cmd[++copy->j] = copy->wc[copy->i];
		copy->i++;
	}
	copy->cmd[copy->j + 1] = 0;
	return (copy->cmd);
}

char	*parsing(char *whole_cmd, t_copy *copy)
{
	copy->i = 0;
	copy->j = -1;
	copy->cmd = NULL;
	copy->args = NULL;
	copy->redir.sstdout = 1;
	copy->redir.sstderr = 2;
	copy->redir.sstdin = 1;
	copy->redir.out1 = NULL;
	copy->redir.out2 = NULL;
	copy->redir.in = NULL;
	copy->wc = whole_cmd;
	g_error = 0;
	copy->cmd = malloc(sizeof(char) * (ft_strlen(copy->wc) + 1));
	printf("copy->cmd : %p malloc\n", copy->cmd);
	if (!(copy->cmd) || !(copy->wc))
		return (NULL);
	copy->cmd[0] = 0;
	while (copy->wc[copy->i] && copy->wc[copy->i] == ' ')
		copy->i++;
	if (cmd(copy) == NULL || g_error == -1)
		return (NULL);
	copy->args = (char **)malloc(sizeof(char *) * 1);
	printf("copy->args : %p malloc\n", copy->args);
	if (!(copy->args) || options(copy, 1, 0) == -1)
		return (NULL);
	return (copy->cmd);
}

/* void print_parsing(char **args, t_redir *redir)
{
	int i = 0;
	int j = 0;
	int test = 0;

	while (args[i])
	{
		printf("arg[%d] = %s\n", i, args[i]);
		i++;
	}
	if (redir->in)
	{
		printf("file stdin = %s\n", redir->in);
		printf("fd stdin = %d\n", redir->sstdin);
	}
	if (redir->out1)
	{
		printf("file stdout = %s\n", redir->out1);
		printf("fd stdout = %d\n", redir->sstdout);
		printf("fin du fichier ? = %d\n", redir->end);
	}
	if (redir->out2)
	{
		printf("file stderr = %s\n", redir->out2);
		printf("fd stderr = %d\n", redir->sstderr);
		printf("fin du fichier ? = %d\n", redir->end);
	}
	printf("g_status = %d\n", g_status);
} */
