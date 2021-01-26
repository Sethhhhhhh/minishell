#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <string.h>
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

typedef	struct	s_redir
{
	int			sstdout;
	int 		sstderr;
	int			sstdin;
	int			end; // a 1 si >> sinon a 0
	char		*out1; // file out pour stdout
	char		*out2; // file out pour stderr
	char		*in; // file in
	int			i;
}				t_redir;

//PARSING
//----------sep.c---------//
t_sep	*parse_sep();
void	print_list(t_sep *list);
//----------pip.c---------//
void    parse_pip(t_sep *list);
void	print_pip_list(t_pip *piplist);
//----------redir.c---------//
int		redirection(char *whole_cmd, t_copy *copy, t_redir *redir);
//----------cmdargs.c---------//
char	*args(char *whole_cmd, t_copy *copy, size_t i, t_redir *redir);
int		options(char *whole_cmd, t_copy *copy, t_redir *redir);
char	*cmd(char *whole_cmd, t_copy *copy, t_redir *redir);
//----------protec.c---------//
int		double_quote(char *whole_cmd, t_copy *copy);
int		simple_quote(char *whole_cmd, t_copy *copy);
int		double_quote_arg(char *whole_cmd, t_copy *copy, size_t i);
int		simple_quote_arg(char *whole_cmd, t_copy *copy, size_t i);
int		simple_quote_redir(char *whole_cmd, t_copy *copy, int i, t_redir *redir, char *str);
int		double_quote_redir(char *whole_cmd, t_copy *copy, int i, t_redir *redir, char *str);
//----------execution.c---------//
void	execution(t_sep *list);




void    ft_pipe(char *str);
int     sys_call(char *cmd, char **paths, char *arg, char **env);

#endif
