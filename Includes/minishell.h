/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 13:46:09 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/14 17:50:59 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libutils.h"

typedef struct s_cmdpath
{
	char			**cmd;
	char			*path;
	char			*str;
}t_cmdpath;

typedef struct s_gnl
{
	int		l;
	int		r;
	char	*buf;
}t_gnl;

typedef struct s_redir
{
	int	in;
	int	out;
	int	inin;
	int	outout;
}t_redir;

typedef struct s_fork
{
	int				wstatus;
	pid_t			childpid;
	struct s_fork	*next;
}t_fork;

typedef struct s_listenv
{
	char				*name;
	char				*value;
	struct s_listenv	*next;
}t_listenv;

typedef struct s_jok
{
	char	*tmp;
	char	*beg;
	char	*end;
	char	**sp;
	char	*sub;
	char	*tmp1;
}t_jok;

typedef struct s_trmkey
{
	char			*on;
	char			*up;
	char			*down;
	char			*right;
	char			*del;
	char			*delk;
	char			*left;
	char			*clear;
	char			*mov_csr;
	char			*save;
	char			*reset;
}t_trmkey;

typedef struct s_hist
{
	char			*cmd;
	struct s_hist	*next;
	struct s_hist	*prev;
}t_hist;

typedef struct s_cmd
{
	char			*cmd;
	struct s_cmd	*next;
}t_cmd;

typedef struct s_int
{
	int		j;
	int		b;
	int		in;
	int		out;
	int		n;
	pid_t	pid;
	int		i_fd;
	int		o_fd;
	size_t	pos;
	int		nb_pipes;
	int		last_exit;
}t_int;

typedef struct s_data
{
	int				*status;
	t_int			*inter;
	int				*my_pipes;
	char			**pip;
	char			*pid_sh;
	char			*prompt;
	char			*sub_str;
	char			*limiter;
	char			*tmp;
	int				heredoc;
	t_cmd			**cmd;
	t_hist			**hist;
	t_hist			*hist_curr_up;
	t_hist			*hist_curr_down;
	t_listenv		**listenv;
	t_listenv		**varquote;
	t_listenv		**var_tmp;
	t_trmkey		*termkey;
	t_fork			**wp;
	struct termios	old_termios;
	struct termios	new_termios;
}t_data;

t_data		*alloc_data(void);
void		init_data(t_data *data, char *r);
t_fork		**list_wp(void);
t_fork		*create_wp(pid_t pid);
void		add_waitpid(t_fork **wp, t_fork *new);
void		gnl_term(char **line, int fd, t_data *data);
void		all_free(t_data *data);
void		ft_pipex(t_data *data);
t_data		*get_shell(char **envp);
void		fcnt_exit(char *r, t_data *data);

void		printer_env(t_listenv **listenv);
t_listenv	**init_listenv(char **envp);
t_listenv	*ft_new_elm(char *name, char *value);
t_listenv	**create_listenv(void);
t_hist		**list_hist(void);
int			fctn_ctrl(t_gnl gnl, t_data *data, char **line);
void		add_hist(t_data *data, char *cmd);
void		free_wp(t_fork **wp);
void		push_back(t_listenv **listenv, t_listenv *new);
void		pop_var(t_listenv **listenv, char *name);
char		*gestion_var(t_data *data, char **cmd_split);
char		*joker_quotes(t_data *data, char *cmd);
size_t		len_value(t_data *data, char *var);
void		add_var(t_data *data, t_listenv **listenv, char *name, char *value);
void		free_lst(t_listenv **lst);
void		free_data(t_data *data);
void		free_hist(t_hist **hist);
size_t		len_variable(char *str);
void		free_lst_cmd(t_cmd **lst);
int			invalid_quote(char *str);
char		*quotes_(t_data *data, char *line_read);

void		check_key_up(t_data *data, char **line);
void		check_key_down(t_data *data, char **line);
void		check_end(t_data *data, char *buf, char **line);
void		check_home(t_data *data, char *buf);
void		check_key_left(t_data *data);
void		check_key_right(t_data *data, char *buf, char **line);
void		trm_backspace(t_data *data, char **line, t_gnl gnl);

t_cmd		**lst_cmd(char *r);
void		manager(t_data *data);
t_cmd		**list_cmd(void);
int			print_error(void);
void		free_data(t_data *data);
t_cmd		*create_cmd(char *cmd);
int			checker_op(char *op, t_data *data);
void		add_cmd(t_cmd **cmd, t_cmd *new);

int			cheker_keys(t_gnl gnl);
void		execute_key(t_data *data, t_gnl gnl, char **line);
void		insert_char(t_data *data, char **line, t_gnl gnl);
void		gnl_term_bis(char **line, t_gnl gnl, t_data *data);
char		*parse_cmd(t_data *data, char *cmd);
void		valid_red(char **cmd, t_data *data, int i);
void		loop_insert_char(int pos, char *dst, char *tmp, t_gnl gnl);

void		write_fd(char *s);
void		limiter(t_data *data);
void		ft_putendl_fd(char *s, int fd);
void		delimiter(char **str, int i, t_data *data, char **path);
int			builti_bis_(t_data *data, char **split, char *cmd);
int			checker_builti(char *r, char **cmd_split, t_data *data);
void		builtin_pwd_echo(t_data *data, char **cmd_split, char *r);

void		close_wait(t_data *data);
void		exec_cmd(t_data *data, t_cmdpath *compath);
void		error_fork(t_data *data);
void		check_last(t_data *data, int i);
void		check_first(t_data *data);
char		*parse_jok(char *str, int i);
char		*reduce_bis(t_data *data, char *str);
char		*rm_quotes(char *cmd);

int			calcul_flag(char *str, int i, int flag);
char		*manager_bis(t_data *data);
void		gand(char *s, t_data *data);
int			ft_chdir(char *r);
void		free_var(char *tmp, char *l);
int			builtin_pwd(void);
int			all_builtin(char *r, char **cmd_split, t_data *data);
int			get_next_line(char **line, int fd);
char		*pop_redir(t_data *data, char **s, char *r, int i);
int			var_bis(t_listenv *tmp, char *name, char *value);
int			search_vari(t_data *data, char **split);
char		*replace_value(t_data *data, char *line);
char		*parse_value(t_data *data, char *value, int t);
char		*_var_mp(t_data *data, char *var, int t);
char		*rl_gets(t_data *data, char *prompt);
char		*ft_substr(char *str, char c);
t_cmd		*loop_cmd(t_data *data, t_cmd *tmp);
void		add_hist(t_data *data, char *cmd);
int			check_echo(t_data *data, char **cmd_split);
char		*new_str_bis(t_data *data, char *cmd_split, char *tmp, char *s_nul);

#endif
