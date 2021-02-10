#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../libft/libft.h"

char **g_envs;

typedef	struct	s_cmd
{
	char	**args;
	char	*cmd;
}				t_cmd;

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
	int				i;
	int				j;
	char			*cmd;
	char			**args;
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
char	*cmd(char *whole_cmd, t_copy *copy, t_redir *redir);
//----------protec.c---------//
int		double_quote(char *whole_cmd, t_copy *copy);
int		simple_quote(char *whole_cmd, t_copy *copy);
int		double_quote_arg(char *whole_cmd, t_copy *copy, size_t i);
int		simple_quote_arg(char *whole_cmd, t_copy *copy, size_t i);
int		simple_quote_redir(char *whole_cmd, t_copy *copy, int i, t_redir *redir, char *str);
int		double_quote_redir(char *whole_cmd, t_copy *copy, t_redir *redir, char *str, int std);
//----------execution.c---------//
void	minishell(t_sep *list);
void	execution(t_copy *cmdarg, t_redir *redir);
//----------varenv.c---------//
int		environnement(char *whole_cmd, t_copy *copy, int arg, int i);
int		environnement_redir(char *whole_cmd, t_copy *copy, int arg, t_redir *redir);

//EXECUTION
//----------syscall.c---------//
void    call(char *cmd, char **args);
t_cmd   *get_cmd(char *line);
//----------env.c---------//
char    *get_env(char *env);
char    *set_env(char *env, char *new_env);
void    print_envs();
char	**get_path();
char    **realloc_envs(size_t size);
ssize_t	find_env(char *env);
size_t  get_envs_count();

//BUILTIN
void	_echo(char **args);
void	_cd(char **args);
void    _pwd();
void	_env();
void	_unset(char **args);
void	_export(char **args);




void    ft_pipe(char *str);
int     sys_call(char *cmd, char **paths, char *arg, char **env);

#endif
