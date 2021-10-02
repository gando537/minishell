/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 17:15:50 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/01 17:53:55 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	exec_over(t_data *data, t_cmdpath *compath, int i)
{
	check_first(data);
	check_last(data, i);
	exec_cmd(data, compath);
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

void	closing(t_data *data)
{
	close_wait(data);
	free_split(data->pip);
	all_free(data);
	exit(0);
}

void	ft_pipex(t_data *data)
{
	int			i;
	t_cmdpath	*compath;

	i = -1; 
	if (data->nb_pipes)
		data->wp = list_wp();
	while (data->pip[++i])
	{
		compath = ft_cmdpath(data->pip, i);
		data->pid = fork();
		if (data->nb_pipes && data->pid != 0)
			add_waitpid(data->wp, create_wp(data->pid));
		if (data->pid == 0)
			exec_over(data, compath, i);
		else if (data->pid < 0)
			error_fork(data);
		data->j += 2;
		free_cmdpath(compath);
	}
	closing(data);
}
