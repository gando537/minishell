/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 17:15:50 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/14 17:52:21 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	exec_over(t_data *data, t_cmdpath *compath, int i)
{
	check_first(data);
	check_last(data, i);
	if (data->inter->b || all_builtin(compath->str, compath->cmd, data))
	{
		data->inter->last_exit = 0;
		return ;
	}
	exec_cmd(data, compath);
}

void	free_cmdpath(t_cmdpath *compath)
{
	free_split(compath->cmd);
	free(compath->path);
	free(compath);
}

t_cmdpath	*ft_cmdpath(t_data *data, int i)
{
	t_cmdpath	*compath;

	compath = malloc(sizeof(t_cmdpath));
	if (!compath)
		return (NULL);
	compath->str = replace_value(data, data->pip[i]);
	compath->cmd = ft_split(compath->str, ' ');
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
	if (data->inter->nb_pipes)
		data->wp = list_wp();
	while (data->pip[++i])
	{
		compath = ft_cmdpath(data, i);
		data->inter->pid = fork();
		if (data->inter->nb_pipes && data->inter->pid != 0)
			add_waitpid(data->wp, create_wp(data->inter->pid));
		if (data->inter->pid == 0)
			exec_over(data, compath, i);
		else if (data->inter->pid < 0)
			error_fork(data);
		data->inter->j += 2;
		data->inter->n--;
		free_cmdpath(compath);
	}
	closing(data);
}
