#ifndef MINISHELL_H
# define MINISHELL_H

/* librairy */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../libft/libft.h"

/* global */

char	**g_envs;
int		g_fork;

/* structures */
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

typedef struct		s_copy
{
	char			**args;
	char			*cmd;
	int				i;
	int				j;
}					t_copy;

typedef	struct	s_redir
{
	char		*out1; // file out pour stdout
	char		*out2; // file out pour stderr
	char		*in; // file in
	int			sstdout;
	int 		sstderr;
	int			sstdin;
	int			end;
	int			i;
}				t_redir;

/* seperation */
t_sep	*parse_sep();
void	print_list(t_sep *list);
t_sep	*add_cell(t_sep *list, char *cmd_sep, int pos);

/* pip */
void    parse_pip(t_sep *list);
void	print_pip_list(t_pip *piplist);

/* redirection */
int		redirection(char *whole_cmd, t_copy *copy, t_redir *redir);

/* cmd & arg */
char	*cmd(char *whole_cmd, t_copy *copy, t_redir *redir);

/* protect */
int		double_quote(char *whole_cmd, t_copy *copy);
int		simple_quote(char *whole_cmd, t_copy *copy);
int		double_quote_arg(char *whole_cmd, t_copy *copy, size_t i);
int		simple_quote_arg(char *whole_cmd, t_copy *copy, size_t i);
int		simple_quote_redir(char *whole_cmd, t_copy *copy, int i, t_redir *redir, char *str);
int		double_quote_redir(char *whole_cmd, t_copy *copy, t_redir *redir, char *str, int std);

/* execution */
void	minishell(t_sep *list);
void	execution(t_copy *cmdarg, t_redir *redir);
void	prompt();

/* Syscall */
void    call(t_copy *cmdarg);

/* env */
char    *get_env(char *env);
char    *set_env(char *env, char *new_env);
void    print_envs();
char	**get_path();
char    **realloc_envs(size_t size);
ssize_t	find_env(char *env);
size_t  get_envs_count();
int		environnement(char *whole_cmd, t_copy *copy, int arg, int i);
int		environnement_redir(char *whole_cmd, t_copy *copy, int arg, t_redir *redir);

/* builtin */
void	_echo(char **args);
void	_cd(char **args);
void    _pwd();
void	_env();
void	_unset(char **args);
void	_export(char **args);

/* handler */
void	sigint_handler(int sign_num);

#endif
