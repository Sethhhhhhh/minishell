/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:53:21 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/13 12:54:45 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	inside_quote(char *str, int i)
{
	char	quote;

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
	return (i);
}

int	syntax_error_redir(char *str, char c)
{
	int		i;
	int		j;

	i = -1;
	while (str[++i])
	{
		j = 0;
		inside_quote(str, i);
		while (str[i] == c || str[i] == ' ')
		{
			if (str[i] == c)
				j++;
			i++;
			if (j == 3)
				return (error_msg(str, i + 1, c));
			if (j > 3)
				return (error_msg(str, i, c));
		}
	}
	return (0);
}

int	syntax_error_newline(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] == '>' || str[i] == '<')
		return (error_msg(str, i, 'n'));
	i++;
	while (str[i--] && (str[i] == ' ' || str[i] == '<' || str[i] == '>'))
	{
		inside_quote(str, i);
		if (str[i] == '>' || str[i] == '<')
			return (error_msg(str, i, 'n'));
	}
	return (0);
}

int	syntax_error_go(char *str, int i, char c)
{
	i--;
	if (str[i] == '|')
		return (error_msg(str, i, c));
	if (syntax_error_redir(str, '>') == -1 || syntax_error_redir(str, '<') == -1
		|| syntax_error_newline(str) == -1)
	{
		g_status = 2;
		return (-1);
	}
	return (0);
}

int	syntax_error(char *str, char c)
{
	int		i;

	i = -1;
	if (str[0] == c)
		return (error_msg(str, 0, c));
	while (str[++i] && (str[i] == ' ' || str[i] == '>'
			|| str[i] == '<' || str[i] == c))
		if (str[i] == c)
			return (error_msg(str, i, c));
	while (str[++i])
	{
		inside_quote(str, i);
		if (str[i] == c)
		{
			while (str[++i] && (str[i] == ' ' || str[i] == '>'
					|| str[i] == '<' || str[i] == c))
				if (str[i] == c)
					return (error_msg(str, i, c));
			if (str[i] == '\0')
				break ;
		}
	}
	return (syntax_error_go(str, i, c));
}
