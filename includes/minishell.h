#ifndef MINISHELL_H
# define MINISHELL_H


#include <stdio.h>
#include <unistd.h>
#include "../libft/libft.h"

typedef	struct	s_sep
{
	char			*cmd_sep;
	struct s_sep	*prev;
	struct s_sep	*next;
	struct s_pip	*pipcell; //si cell est == à NULL c'est qu'il n'y a pas de pipes dans cmd_sep
}				t_sep;

typedef	struct	s_pip
{
	char			*cmd_pip;
	struct s_pip	*prev;
	struct s_pip	*next;
}				t_pip;

typedef	struct	s_env
{
	char			**paths;
	char			**env;
}				t_env;

typedef struct		s_copy
{
	int i;
	int j;
	char *cmd;
	char **args;
}					t_copy;

//PARSING
//----------sep.c---------//
t_sep	*parse_sep();
void	print_list(t_sep *list);
//----------pip.c---------//
void    parse_pip(t_sep *list);
void	print_pip_list(t_pip *piplist);
//----------redir.c---------//
int		redir_out(char *whole_cmd, t_copy *copy);

void    ft_pipe(char *str);
int     sys_call(char *cmd, char **paths, char *arg, char **env);

#endif
