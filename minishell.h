/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 13:46:09 by mdiallo           #+#    #+#             */
/*   Updated: 2021/09/02 20:24:31 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <termios.h>
# include <sys/signal.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_bool
{
	false,
	true
}t_bool;

typedef struct s_ind
{
	int	i;
	int	j;
	int	w_len;
}t_ind;

typedef struct s_cmdpath
{
	char			**cmd;
	char			*path;
}t_cmdpath;

typedef struct s_redir
{
	int	in;
	int	out;
	int	inin;
	int	outout;
}t_redir;

typedef struct s_fork
{
	int			wstatus;
	pid_t		childpid;
}t_fork;

typedef struct s_listenv
{
	char				*name;
	char				*value;
	struct s_listenv	*next;
}t_listenv;


typedef struct s_data
{
	int			*status;
	int			i;
	int			j;
	int			k;
	int			l;
	int			x;
	int			in;
	int			i_fd;
	int			o_fd;
	int			c;
	pid_t		pid;
	int			nb_pipes;
	t_listenv	**listenv;
	t_listenv	**var_tmp;
}t_data;

t_data		*alloc_data(void);
size_t		ft_strlen(char *str);
int			ft_is_whitespace(char c);
char		**ft_split(char *s, char c);
int			len_split(char **split);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strcmp(char *s1, char *s2);
int			get_next_line(char **line, int fd);
char		*get_path(char *cmd);
void		all_free(t_data *data, int *my_pipes);
void		free_split(char **split);
void		ft_strdel(char **as);
int 		check_pip(char **cmd);
int			*creat_pipe(int nb_pipes);
void    	ft_pipex(char *r, int nb_pip, t_data *data);
int			check_pip(char **cmd);
int 		check_file_exist(const char* filename);
t_bool		ft_checker_cmd(char *r, char **cmd_split, 
			struct termios old_termios, t_data *data);

char		*ft_strndup(const char *s, size_t n);
char		*ft_strdup(const char *src);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strcat(char *dest, char *src);
char		*ft_strncat(char *dest, char *src, int nb);
char		*ft_strstr(char *str, char *to_find);
void    	str_replace(char *str, char *rech, char *remp);

int			ft_nbre(char *str);

void		printer_env(t_listenv **listenv);
t_listenv	**init_listenv(char **envp);
t_listenv	*ft_new_elm(char *name, char *value);
t_listenv	**create_listenv(void);
void		push_back(t_listenv **listenv, t_listenv *new);
void		pop_var(t_listenv **listenv, char *name);
void		add_var(t_listenv **listenv, char *name, char *value);
void		free_lst(t_listenv **lst);
void		free_data(t_data *data);

#endif