/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:59:30 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/14 18:26:18 by mdiallo          ###   ########.fr       */
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
	if (data->tmp)
		unlink(data->tmp);
	free(data->my_pipes);
	data->inter->in = 0;
	data->inter->nb_pipes = 0;
	data->inter->o_fd = 1;
	data->inter->i_fd = 0;
	data->inter->j = 0;
}

void	fcnt_exit(char *r, t_data *data)
{
	if (ft_strcmp(r, "exit") == 0)
	{
		printf("exit\n");
		tcsetattr(0, TCSANOW, &data->old_termios);
		free_data(data);
		exit(0);
	}
}
