#include "../../includes/minishell.h"

void	ft_error_token(char *msg, char c, int i, char *str)
{
	printf("bash: %s", msg);
	if (c == 'n')
		printf("newline'\n");
	else if (str[i - 1] == c || str[i + 1] == c)
		printf("%c%c'\n", c, c);
	else
		printf("%c'\n", c);
	exit(0);
}

void	ft_error_quote(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

void	syntax_error_redir(char *str, char c)
{
	int i;
	int j = -1;
	char quote;

	i = -1;
	while (str[++i])
	{
		j = 0;
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
		while (str[i] == c || str[i] == ' ')
		{
			if (str[i] == c)
				j++;
			i++;
			if (j > 2)
				ft_error_token("syntax error near unexpected token `", c, i + 1, str);
			if (j > 3)
				ft_error_token("syntax error near unexpected token `", c, i, str);
		}
	}
}

void	syntax_error_newline(char *str)
{
	int i;
	char quote;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] == '>' || str[i] == '<')
			ft_error_token("syntax error near unexpected token `", 'n', i, str);
	i++;
	while (str[i--] && (str[i] == ' ' || str[i] == '<' || str[i] == '>'))
	{
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
		if (str[i] == '>' || str[i] == '<')
			ft_error_token("syntax error near unexpected token `", 'n', i, str);
	}
}

void	syntax_error(char *str, char c)
{
	int i;
	char quote;

	i = -1;
	if (str[0] == c)
	{
		//printf("i = %d, str[i] = %c\n", i, str[i]);
		//printf("i = %d, str[i] = %c\n", i + 1, str[i + 1]);
		ft_error_token("syntax error near unexpected token `", c, 0, str);
	}
	while (str[++i] && (str[i] == ' ' || str[i] == '>' || str[i] == '<' || str[i] == c))
		if (str[i] == c) 
			ft_error_token("syntax error near unexpected token `", c, i, str);
	while (str[++i])
	{
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
		if (str[i] == c)
		{
			while (str[++i] && (str[i] == ' ' || str[i] == '>' || str[i] == '<' || str[i] == c))
				if (str[i] == c)
					ft_error_token("syntax error near unexpected token `", c, i, str);
			if (str[i] == '\0')
				break;
		}
	}
	i--;
	if (str[i] == '|')
		ft_error_token("syntax error near unexpected token `", c, i, str);
	syntax_error_redir(str, '>');
	syntax_error_redir(str, '<');
	syntax_error_newline(str);
}

void	ft_error_exit(char *str, char *msg)
{
	printf("bash: %s", str);
	if (errno != 0)
		printf(": %s\n", strerror(errno));
	else
		printf(": %s\n", msg);
	exit(0);
}