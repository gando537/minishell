/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libutils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 13:46:09 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/05 16:09:27 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBUTILS_H
# define LIBUTILS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> 
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <ncurses.h>
# include <term.h>
# include <signal.h>
# include <string.h>
# include <errno.h>

typedef struct s_ind
{
	int	i;
	int	j;
	int	w_len;
}t_ind;

void		ft_putchar_fd(char c, int fd);
size_t		ft_strlen(char *str);
int			ft_isspace(char c);
char		*ft_itoa(int n);
int			len_split(char **split);
char		*get_path(char *cmd);
void		free_split(char **split);
int			check_pip(char **cmd);
int			*creat_pipe(int nb_pipes);
int			check_redir(char *r);
int			check_file_exist(const char	*filename);
int			ft_checker_cmd(char *r, char **cmd_split);

char		*substr(char *str);
int			ft_putchar(int c);
void		ft_strdel(char **as);
int			ft_strcmp(char *s1, char *s2);
void		search_c(char *s);
int			search_char(char *s, int c);
char		**ft_split(char *s, char c);
char		*ft_strjoin(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, int n);
char		*ft_strndup(const char *s, size_t n);
char		*ft_strdup(const char *src);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strcat(char *dest, char *src);
char		*ft_strncat(char *dest, char *src, int nb);
char		*ft_strstr(char *str, char *to_find);
void		ft_putstr_fd(char *s, int fd);
void		ft_cpy(char *beg, char *end, char *src);
void		str_replace(char *str, char *rech, char *remp);

void		print_banner(void);
int			ft_nbre(char *str);
char		*ft_pos(char *name, char *sub_str);
char		*parse_sub(char *sub_str);
void		replace_escap(char *s);
char		*reduce_m(char **sp, char *end);

void		move_cursor_left(size_t *s, char *left);
size_t		get_non_escaped(char *str, size_t i, char *sep);
int			is_first_char(char *str, char *set);
int			is_last_char(char *str, char *set);
size_t		find_char(char *s, char c);
int			valid_syntax(char *line);
int			ft_isinset(int c, char *set);
char		*replik_j(char *str, char *name);
char		*joker_bis(void);
char		*joker(char *r, char *sub_str);
char		*joker_m(char *str, char *sub_str, struct dirent *entry, int i);

char		*clear_sc(void);
void		display_right(int i, char **line);
char		*display_prompt(void);
char		*parse_r(char *r);
char		*stripwhite(char *string);
int			checker_path(char *p_r);

int			replace_in(char *s, int i);
int			replace_inin(char *s, int i);
int			replace_out(char *s, int i);
int			replace_outout(char *s, int i);
int			replace_pip(char *s, int i);
void		replace_andor(char *s);

char		*redirection(char *r);

#endif