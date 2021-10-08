/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_pip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:23:22 by mdiallo           #+#    #+#             */
/*   Updated: 2021/01/01 02:57:02 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	check_first(t_data *data)
{
	if (data->j != 0)
	{
		if (dup2(data->my_pipes[data->j - 2], 0) < 0)
		{
			all_free(data);
			perror("dup2");
			exit(1);
		}
	}
	else if (data->j == 0 && data->in == 1)
	{
		close(0);
		if (dup(data->i_fd) < 0)
		{
			all_free(data);
			perror("dup");
			exit(1);
		}
	}
}

void	check_last(t_data *data, int i)
{
	if (data->nb_pipes != i)
	{
		if (dup2(data->my_pipes[data->j + 1], 1) < 0)
		{
			all_free(data);
			perror("dup2");
			exit(1);
		}
	}
	else
	{
		if (dup2(data->o_fd, 1) < 0)
		{
			all_free(data);
			perror("dup2");
			exit(1);
		}
	}
}

void	error_fork(t_data *data)
{
	all_free(data);
	perror("error");
	exit(1);
}

void	exec_cmd(t_data *data, t_cmdpath *compath)
{
	int	i;

	i = 0;
	while (i < 2 * data->nb_pipes)
	{
		close(data->my_pipes[i]);
		i++;
	}
	if (compath->path != NULL)
	{
		if (execve(compath->path, compath->cmd, NULL) < 0)
		{
			perror(compath->cmd[0]);
			all_free(data);
			exit(1);
		}
		exit(0);
	}
	perror(compath->cmd[0]);
}

void	close_wait(t_data *data)
{
	int		k;
	t_fork	*tmp;

	k = 0;
	while (k < 2 * data->nb_pipes)
	{
		close(data->my_pipes[k]);
		k++;
	}
	if (data->nb_pipes == 0)
	{
		wait(data->status);
		free_split(data->pip);
		all_free(data);
		exit(0);
	}
	tmp = *(data->wp);
	while (tmp)
	{
		waitpid(tmp->childpid, &(tmp->wstatus), WUNTRACED | WCONTINUED);
		tmp = tmp->next;
	}
	free_wp(data->wp);
}
