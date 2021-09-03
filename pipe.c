/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 17:15:50 by mdiallo           #+#    #+#             */
/*   Updated: 2021/09/03 00:01:02 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pip(char **cmd)
{
	int i;
	int nb_pip;

	nb_pip = 0;
	if (len_split(cmd) <= 1)
		return (nb_pip);
	i = 1;
	while (cmd[i])
		if (ft_strcmp(cmd[i++], "|") == 0)
			nb_pip++;
	return (nb_pip);
}

int	*creat_pipe(int nb_pipes)
{
	int	i;
	int	*_pipes;

	_pipes = (int *)malloc(sizeof(int) * 2 * nb_pipes);
	if (!_pipes)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(_pipes + i * 2) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (_pipes);
}

t_data	*alloc_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->c = 0;
	return (data);
}

int	search_str(char **tab, char *str)
{
	int	i;

	i = 0;
	while (tab[i])
		if (ft_strcmp(tab[i++], str) == 0)
			break ;
	if (ft_strcmp(tab[--i], str) != 0)
		return (0);
	return (i);
}

int check_file_exist(const char* filename)
{
	struct stat	buffer;
	int			exist;
	
	exist = stat(filename, &buffer);
	if (exist == 0)
		return (1);
	return (0);
}

char	**input_file(char *r, char **cmd, t_data *data, char **pip)
{
	char	*s;
	char	**p;
	char	*tmp;
	size_t	len;

	data->in = 1;
	if (len_split(cmd) <= 1)
	{
		free_split(cmd);
		free_split(pip);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	free_split(pip);
	s = r;
	while (*s != '<')
		s++;
	len = ft_strlen(cmd[1]) + 3;
	data->i_fd = open(cmd[1], O_RDONLY);
	tmp = s + len;
	p = ft_split(tmp, '|');
	return (p);
}

void	output_file(char **cmd, t_data *data, char **pip)
{
	int	len;
	int pos;

	len = len_split(cmd);
	pos = search_str(cmd, ">");
	if (len <= 1 || pos == len - 1)
	{
		free_split(cmd);
		free_split(pip);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	data->o_fd = open(cmd[len_split(cmd) - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
}

// t_redir	*init_redir()
// {
// 	t_redir	*redir;

// 	redir = malloc(sizeof(t_redir));
// 	if (!redir)
// 		return (NULL);
// 	redir->in = 0;
// 	redir->inin = 0;
// 	redir->out = 0;
// 	redir->outout = 0;
// 	return (redir);
// }

char	**init_data(t_data *data, int **my_pipes, int nb_pip, char *r)
{
	char	**pip;
	char	**cmd;
	// t_redir	*redir;

	pip = ft_split(r, '|');
	cmd = ft_split(r, ' ');
	// redir = init_redir();
	data->in = 0;
	data->nb_pipes = nb_pip;
	if (ft_strcmp(cmd[0], "<") == 0)
		pip = input_file(r, cmd, data, pip);
	data->o_fd = 1;
	if (search_str(cmd, ">"))
		output_file(cmd, data, pip);
	*my_pipes = creat_pipe(data->nb_pipes);
	data->j = 0;
	free(r);
	free_split(cmd);
	return (pip);
}

t_bool	checker_arg(char *cmd)
{
	if (ft_strcmp(cmd, "<") == 0
		|| ft_strcmp(cmd, ">") == 0
		|| ft_strcmp(cmd, "|") == 0)
		return (true);
	return (false);
}

void	check_first(t_data *data, int *my_pipes)
{
	if (data->j != 0)
	{
		if (dup2(my_pipes[data->j - 2], 0) < 0)
		{
			all_free(data, my_pipes);
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	else if (data->j == 0 && data->in == 1)
	{
		close(0);
		if (dup(data->i_fd) < 0)
		{
			all_free(data, my_pipes);
			perror("dup");
			exit(EXIT_FAILURE);
		}
	}
}

void	check_last(t_data *data, int *my_pipes, int i)
{
	if (data->nb_pipes != i)
	{
		if (dup2(my_pipes[data->j + 1], 1) < 0)
		{
			all_free(data, my_pipes);
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	if (data->nb_pipes == i)
	{
		if (dup2(data->o_fd, 1) < 0)
		{
			all_free(data, my_pipes);
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
}

void	error_fork(t_data *data, int *my_pipes)
{
	all_free(data, my_pipes);
	perror("error");
	exit(EXIT_FAILURE);
}

void	exec_cmd(t_data *data, t_cmdpath *compath, int *my_pipes)
{
	data->i = 0;
	while (data->i < 2 * data->nb_pipes)
	{
		close(my_pipes[data->i]);
		data->i++;
	}
	if (compath->path != NULL)
	{
		if (search_str(compath->cmd, ">"))
			compath->cmd[search_str(compath->cmd, ">")] = (char *)NULL;
		if (execve(compath->path, compath->cmd, NULL) < 0)
		{
			all_free(data, my_pipes);
			perror(compath->cmd[0]);
			exit(EXIT_FAILURE);
		}
	}
	perror(compath->cmd[0]);
}

void	close_wait(t_data *data, int *my_pipes)
{
	data->k = 0;
	while (data->k < 2 * data->nb_pipes)
	{
		close(my_pipes[data->k]);
		data->k++;
	}
	data->l = 0;
	while (data->l < data->nb_pipes + 1)
	{
		wait(data->status);
		data->l++;
	}
}

void	exec_over(t_data *data, t_cmdpath *compath, int *my_pipes, int i)
{
		check_first(data, my_pipes);
	check_last(data, my_pipes, i);
	exec_cmd(data, compath, my_pipes);
}

void	free_cmdpath(t_cmdpath *compath)
{
	free_split(compath->cmd);
	free(compath->path);
	free(compath);
}

t_cmdpath	*ft_cmdpath(char **pip, int i)
{
	t_cmdpath	*compath;

	compath = malloc(sizeof(t_cmdpath));
	if (!compath)
		return (NULL);
	compath->cmd = ft_split(pip[i], ' ');
	compath->path = get_path(compath->cmd[0]);
	return (compath);
}

void	ft_pipex(char *r, int nb_pip, t_data *data)
{
	int			*my_pipes;
	char		**pip;
	int			i;
	t_cmdpath	*compath;

	pip = init_data(data, &my_pipes, nb_pip, r);
	i = 0;
	while (pip[i])
	{
		compath = ft_cmdpath(pip, i);
		data->pid = fork();
		if (data->pid == 0)
			exec_over(data, compath, my_pipes, i);
		else if (data->pid < 0)
			error_fork(data, my_pipes);
		data->j += 2;
		free_cmdpath(compath);
		i++;
	}
	close_wait(data, my_pipes);
	free_split(pip);
	all_free(data, my_pipes);
	exit(0);
}
