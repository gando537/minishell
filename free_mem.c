/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:59:30 by mdiallo           #+#    #+#             */
/*   Updated: 2021/01/01 02:18:59 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	free_lst(t_listenv **lst)
{
	t_listenv	*tmp;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		if (tmp->name)
			ft_strdel(&tmp->name);
		if (tmp->value)
			ft_strdel(&tmp->value);
		tmp = tmp->next;
	}
	free(lst);
}

void	free_hist(t_hist **lst)
{
	t_hist	*tmp;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		ft_strdel(&tmp->cmd);
		tmp = tmp->next;
	}
	free(lst);
}

void	free_wp(t_fork **wp)
{
	t_fork	*tmp;
	t_fork	*curr;

	if (!wp)
		return ;
	tmp = *wp;
	curr = tmp;
	while (tmp)
	{
		tmp = tmp->next;
		free(curr);
		curr = tmp;
	}
	free(wp);
}

void	all_free(t_data *data)
{
	free(data->my_pipes);
	data->in = 0;
	data->nb_pipes = 0;
	data->o_fd = 1;
	data->i_fd = 0;
	data->j = 0;
}

void	fcnt_exit(char *r, t_data *data)
{
	if (ft_strcmp(r, "exit") == 0)
	{
		tcsetattr(0, TCSANOW, &data->old_termios);
		free_data(data);
		exit(0);
	}
}
