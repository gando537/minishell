/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 13:43:30 by mdiallo           #+#    #+#             */
/*   Updated: 2021/09/02 22:29:43 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*part_path;

	i = 0;
	while (paths[i] && cmd[1] != '/')
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		ft_strdel(&part_path);
		if (check_file_exist(path))
			return (path);
		ft_strdel(&path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd)
{
	char	**paths;
	char	*envp;
	char	*pth;

	envp = getenv("PATH");
	paths = ft_split(envp, ':');
	pth = search_path(paths, cmd);
	free_split(paths);
	return (pth);
}

char	*parse_r(char *r)
{
	char	*p_r;
	char	*tmp;

	tmp = r;
	while (*tmp != '\0')
	{
		if (ft_is_whitespace(*tmp))
		{
			p_r = tmp;
			while (ft_is_whitespace(*tmp))
			{
				tmp++;
				if (*tmp == '\0')
					*p_r = '\0';
			}
		}
		else
			tmp++;
	}
	return (r);
}

char	*stripwhite(char *string)
{
	char	*s;
	char	*t;

	s = string;
	while (ft_is_whitespace(*s))
		s++;
	if (*s == 0)
    	return (s);
	t = s + ft_strlen (s) - 1;
	while (t > s && ft_is_whitespace (*t))
		t--;
	*++t = '\0';
	return (s);
}

char	*rl_gets(char *prompt)
{
	char	*line_read;
	char	*prmpt;
	char	*hist;

	line_read = (char *)NULL;
	if (line_read)
	{
		free(line_read);
		line_read = (char *)NULL;
	}
	prmpt = ft_strjoin(prompt, " ");
	line_read = readline(prmpt);
	if (*prompt)
		free(prompt);
	free(prmpt);
	hist = stripwhite(line_read);
	if (hist && *hist)
		add_history(hist);
	return (line_read);
}

char	*display_prompt()
{
	char	path[255];
	char	*res;
	char	*res1;
	char	*res2;
	char	**rep;

	getcwd(path, 255);
	res = ft_strjoin("\033[34;01m[\033[33mroot@\033[035m", getenv("USER"));
	res1 = ft_strjoin(res, "\033[34;01m]\033[36m $ ");
	free(res);
	rep = ft_split(path, '/');
	if (ft_strcmp(path, "/") == 0)
		res2 = ft_strjoin(res1, "/");
	else if (ft_strcmp(getenv("USER"), rep[len_split(rep) - 1]) == 0)
		res2 = ft_strjoin(res1, "~");
	else
		res2 = ft_strjoin(res1, rep[len_split(rep) - 1]);
	res = ft_strjoin(res2, "\033[00m");
	free(res1);
	free(res2);
	free_split(rep);
	return(res);
}

// static void	ft_execmd(char *path, char **cmd_split)
// {
// 	int 	wstatus;
// 	pid_t	childpid;

// 	childpid = fork();
// 	if (childpid == 0)
// 	{
// 		execve(path, cmd_split, NULL);
// 		exit(0);
// 	}
// 	waitpid(childpid, &(wstatus), WUNTRACED | WCONTINUED);
// 	kill(childpid, SIGTERM);
// 	if (ft_strcmp(cmd_split[0], "echo") == 0
// 		&& ft_strcmp(cmd_split[1], "-n") == 0)
// 		printf("%%\n");
// 	if (ft_strcmp(cmd_split[0], "cat") == 0)
// 		printf("\n");
// }

void	checker_path(char *p_r)
{
	if (opendir(p_r) == NULL)
		perror(p_r);
	chdir(p_r);
}

void	ft_chdir(char *r)
{
	char	*p_r;
	
	if (ft_strlen(r) < 3)
		chdir(getenv("HOME"));
	else
	{
		p_r = &r[3];
		checker_path(p_r);
	}
}

// void	manager(struct termios old_termios)
// {
// 	// char	*path;
// 	char	**cmd_split;
// 	char 	*r;
// 	char	*prompt;
// 	int		nb_pip;

// 	prompt = display_prompt();
// 	r = rl_gets(prompt);
// 	cmd_split = ft_split(r, ' ');
// 	nb_pip = check_pip(cmd_split);
// 	if (ft_strlen(r) == 0 || ft_checker_cmd(r, cmd_split, old_termios))
// 	{
// 		free(r);
// 		return;
// 	}
// 	if (ft_strcmp(cmd_split[0], "cd") == 0)
// 		ft_chdir(r);
// 	// if (nb_pip > 0)
// 	// {
	
// 	// }
// 	free_split(cmd_split);
// 	ft_pipex(r, nb_pip);
// 	return ;

// 	// else
// 	// {
// 	// 	path = get_path(cmd_split[0]);
// 	// 	ft_execmd(path, cmd_split);
// 	// }
// 	// free(r);
// 	// free_split(cmd_split);
// }

t_bool	checker(char *r, char **cmd_split, 
		struct termios old_termios, t_data *data)
{
	if (ft_strlen(r) == 0
		|| ft_checker_cmd(r, cmd_split, old_termios, data))
	{
		free(r);
		return (true);
	}
	if (ft_strcmp(cmd_split[0], "cd") == 0)
	{
		ft_chdir(r);
		return (true);
	}
	if (ft_strcmp(cmd_split[0], "env") == 0
		|| ft_strcmp(cmd_split[0], "printenv") == 0)
	{
		printer_env(data->listenv);
		return (true);
	}
	return (false);
}

t_bool	check_redir(char *r)
{
	if (ft_strstr(r, "<")
		|| ft_strstr(r, ">")
		|| ft_strstr(r, "<<")
		|| ft_strstr(r, ">>"))
		return (true);
	return (false);
}

char	*redirection(char *r)
{	
	char	*new_r;
	int		nb;
	
	nb = ft_nbre(r);
	new_r = ft_strndup(r,ft_strlen(r) + (nb * 2));
	free(r);
	str_replace(new_r, "< ", "<");
	str_replace(new_r, " <", "<");
	str_replace(new_r, "<", " < ");
	str_replace(new_r, "<< ", "<<");
	str_replace(new_r, " <<", "<<");
	str_replace(new_r, "<<", " << ");
	str_replace(new_r, "> ", ">");
	str_replace(new_r, " >", ">");
	str_replace(new_r, ">", " > ");
	str_replace(new_r, ">> ", ">>");
	str_replace(new_r, " >>", ">>");
	str_replace(new_r, ">>", " >> ");
	str_replace(new_r, "| ", "|");
	str_replace(new_r, " |", "|");
	str_replace(new_r, "|", " | ");
	return (new_r);
}

t_bool	search_char(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		if (s[i++] == c)
			return (true);
	return (false);	
}

void	gand(char *s, t_data *data)
{
	char		**split;
	t_listenv	*tmp;

	if (search_char(s, '='))
	{
		split = ft_split(s, '=');
		add_var(data->listenv, split[0], split[1]);
		free_split(split);
		return ;
	}
	tmp = *(data->var_tmp);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, s) == 0)
		{
			add_var(data->listenv, s, tmp->value);
			pop_var(data->var_tmp, s);
			return ;
		}
		tmp = tmp->next;
	}
}

void	var_val(t_data *data, char *str)
{
	char		**split;

	split = ft_split(str, '=');
	if (len_split(split) == 2)
		add_var(data->var_tmp, split[0], split[1]);
}

t_bool	_bis_(t_data *data, char **split)
{
	if (search_char(split[0], '='))
	{
		var_val(data, split[0]);
		free_split(split);
		return (true);
	}
	if (ft_strcmp(split[0], "export") == 0)
	{
		if (split[1])
			gand(split[1], data);
		free_split(split);
		return (true);
	}
	if (ft_strcmp(split[0], "unset") == 0)
	{
		if (split[1])
			pop_var(data->listenv, split[1]);
		free_split(split);
		return (true);
	}
	return (false);
}

char	*manager_bis(t_data *data)
{
	char 	*r;
	char	*prompt;
	char	**split;

	prompt = display_prompt();
	r = rl_gets(prompt);
	if (check_redir(r))
		r = redirection(r);
	split = ft_split(r, ' ');
	if (*split)
		if (_bis_(data, split))
			return ((char *)NULL);
	free_split(split);
	return (r);
}

void	manager(struct termios old_termios, t_data *data)
{
	char	**cmd_split;
	int		nb_pip;
	t_fork	fork_;
	char 	*r;

	r = manager_bis(data);
	if (!r)
		return ;
	cmd_split = ft_split(r, ' ');
	nb_pip = check_pip(cmd_split);
	if (checker(r, cmd_split, old_termios, data))
		return ;
	fork_.childpid = fork();
	if (fork_.childpid == 0)
		ft_pipex(r, nb_pip, data);
	waitpid(fork_.childpid, &(fork_.wstatus), WUNTRACED | WCONTINUED);
	free_split(cmd_split);
}

void    sig_handler(int signum)
{
    if (signum == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
    	rl_replace_line("", 0);
        rl_redisplay();
    }
	else if (signum == SIGQUIT)
		exit(0);
}

int	len_liste(t_listenv **liste)
{
	int	i;
	t_listenv *tmp;

	i = 0;
	tmp = *liste;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_listenv	**init_listenv(char **envp)
{
	int			i;
	char		**sp;
	t_listenv	*new;
	t_listenv	**listenv;

	listenv = create_listenv();
	if (!envp)
		return (listenv);
	i = 0;
	while (envp[i])
	{
		sp = ft_split(envp[i], '=');
		new = ft_new_elm(sp[0], sp[1]);
		push_back(listenv, new);
		free_split(sp);
		i++;
	}
	return (listenv);
}

void	printer_env(t_listenv **listenv)
{
	t_listenv	*tmp;

	if (!*listenv)
		return ;
	tmp = *listenv;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void	clear()
{
	char	**cl;
	char	*path;
	pid_t	childpid;
	int		wstatus;

	cl = ft_split("clear", ' ');
	path = get_path("clear");
	childpid = fork();
	if (childpid == 0)
	{
		execve(path, cl, NULL);
		exit (0);
	}
	waitpid(childpid, &(wstatus), WUNTRACED | WCONTINUED);
	free(path);
	free_split(cl);
}

void	free_data(t_data *data)
{
	free_lst(data->listenv);
	free_lst(data->var_tmp);
	free(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data			*data;
	struct termios	old_termios;
	struct termios	new_termios;

	(void)argc;
	(void)argv;
	data = alloc_data();
	data->listenv = init_listenv(envp);
	data->var_tmp = init_listenv((char **)NULL);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	tcgetattr(0,&old_termios);
	new_termios = old_termios;
	new_termios.c_cc[VQUIT] = 4;
	new_termios.c_cc[VINTR] = 3;
	tcsetattr(0,TCSANOW,&new_termios);
		// clear();
	// chdir(getenv("HOME"));
	while (true)
		manager(old_termios, data);
	free_data(data);
	tcsetattr(0,TCSANOW,&old_termios);
	return (0);
}