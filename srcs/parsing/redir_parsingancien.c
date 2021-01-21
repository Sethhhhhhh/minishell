//#include "../../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

typedef	struct	s_redir
{
	int			stdout;
	int 		stderr;
    int 	    stdin;
	char        *data;
    int         end;
}				t_redir;

void    ft_error(char *str)
{
    printf("%s\n", str);
    exit(0);
}

int			ft_strlen(char *str)
{
	int			i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int    unexpected(char *str)
{
    int i;
    int left;
    int right;
    int need;

    i = -1;
    while (str[++i])
    {
        left = 0;
        right = 0;
        need = (str[i] == '>') ? 2 : 1;
        while (str[i] == '>')
        {
            left++;
            i++;
        }
        while (str[i] == '<')
        {
            right++;
            i++;
        }
        if (right > need || left > need)
        {
            if (right > need && right > 4)
                ft_error("bash: syntax error near unexpected token `<<'\n");
            else if (right > need && right <= 4)
                ft_error("bash: syntax error near unexpected token `<'\n");
            else if (left > need && left > 3)
                ft_error("bash: syntax error near unexpected token `>>'\n");
            else if (left > need && left <= 3)
                ft_error("bash: syntax error near unexpected token `>'\n");
            return (0);
        }
    }
    return (1);
}

int    unexpected2(char *str)
{
    int i;
    int ok;
    i = -1;
    while (str[++i])
    {
        if (str[i] == '>' && str[i + 1] != '>')
        {
            i = i + 1;
            ok = 0;
            while (str[i] != '>' && str[i])
            {
                if ((str[i] >= 33 && str[i] < 60) || (str[i] > 62 && str[i] <= 126) || (str[i] == 61))
                {
                    ok = 1;
                    break;
                }
                i++;
            }
            if (i == ft_strlen(str) && ok == 0)
                    ft_error("bash: syntax error near unexpected token `newline'");
            if (str[i] == '>' && ok == 0)
                ft_error("bash: syntax error near unexpected token `>'");
        }
        if (str[i] == '>' && str[i + 1] == '>')
            i = i + 1;
        if (str[ft_strlen(str) - 1] == '>')
            ft_error("bash: syntax error near unexpected token `newline'");
    }
    return (1);
}

int    parse_redir(char *str)
{
    if (unexpected(str) == 0)
        return (0);
    unexpected2(str);
    return (0); 
}

int     main()
{
    //char *str = "echo bonjour > coucou";
    char *str = "e> >cho hey ";
    parse_redir(str);
}