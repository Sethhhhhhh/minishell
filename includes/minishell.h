/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:10:16 by yviavant          #+#    #+#             */
/*   Updated: 2019/11/14 18:28:42 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** libraries
*/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include "../libft/libft.h"

/*
** global
*/
char					**g_envs;
pid_t					g_pid;
int						g_error;
int						g_status;

/*
** structures
*/
typedef	struct			s_sep
{
	char				*cmd_sep;
	struct s_sep		*prev;
	struct s_sep		*next;
	struct s_pip		*pipcell;
}						t_sep;

typedef	struct			s_pip
{
	char				*cmd_pip;
	struct s_pip		*prev;
	struct s_pip		*next;
}						t_pip;

typedef	struct			s_redir
{
	char				*out1;
	char				*out2;
	char				*in;
	int					sstdout;
	int					sstderr;
	int					sstdin;
	int					end;
	int					i;
}						t_redir;

typedef struct			s_copy
{
	char				*wc;
	char				**args;
	char				*cmd;
	int					i;
	int					j;
	t_redir				redir;
}						t_copy;

/*
** separation
*/
t_sep					*parse_sep();
void					print_list(t_sep *list);
t_sep					*add_cell(t_sep *list, char *cmd_sep, int pos);
void					free_list(t_sep *list);

/*
** pip
*/
void					parse_pip(t_sep *list);
void					print_pip_list(t_pip *piplist);
int						run_pipe(t_pip *pipcell, t_copy *cmdargs, int fdd);
int						status_child(pid_t	g_pid);

/*
** redirection
*/
int						redirection(t_copy *copy);
int						redir_quoting(t_copy *copy, int i, char *file);
int						redir_out(t_copy *copy);
int						redir_out_error(t_copy *copy);
int						create_file(t_copy *copy, int type);

/*
** cmd & arg
*/
char					*parsing(char *whole_cmd, t_copy *copy);
int						options(t_copy *copy, size_t i, size_t	j);
char					*args(t_copy *copy, size_t i);

/*
** protect
*/
int						quote_error(char c);
int						d_quote(t_copy *copy, int j);
int						s_quote(t_copy *copy);
int						d_quote_arg(t_copy *copy, size_t i, int j);
int						s_quote_arg(t_copy *copy, size_t i);
int						s_quote_redir(t_copy *copy, char *str);
int						d_quote_redir(t_copy *copy, char *str, int std);

/*
** execution
*/
void					minishell(t_sep *list);
void					execution(t_copy *cmdarg, int pipe);
void					prompt();
int						exec(char **args, int pipe);
int						check_builtin(char **args);
int						check_bins(char **args, int pipe);
int						has_perm(char **args, char *bin, struct stat statbuf,
						int pipe);
int						run(char **args, char *bin, int pipe);
int						return_error(char *cmd, char *msg, int ret, int status);

/*
** syscall
*/
void					call(t_copy *cmdarg);

/*
** env
*/
char					*get_env(char *env);
int						set_env(char *env, char *new_env);
void					print_envs();
char					**get_path();
char					**realloc_envs(size_t size);
ssize_t					find_env(char *env);
size_t					get_envs_count();
int						env(t_copy *copy, int arg, int i, int space);
int						env_redir(t_copy *copy, int arg, int space);
int						no_value(t_copy *copy, char *value);
int						status_env(t_copy *copy, int arg, int i);
void					env_copy(t_copy *copy, int arg, int i, char *value);

/*
** builtin
*/
int						run_echo(char **args);
int						run_cd(char **args);
int						run_unset(char **args);
int						run_export(char **args);
void					sort_env(void);
int						run_env(void);
int						set_directory(char *path);
void					run_exit(char **args);
int						check_export_name(char *args);

/*
** handler
*/
void					sigint_handler(int sign_num);

/*
** errors
*/
int						error_exit(char *str, char *msg);
int						syntax_error(char *str, char c);
int						error_msg(char *str, int i, char c);
void					error_ambiguous(char *name);
void					free_cmdarg(t_copy *copy);


void					print_parsing(char **args, t_redir *redir);

#endif
