/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_up_down.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 09:55:18 by mdiallo           #+#    #+#             */
/*   Updated: 2021/01/01 02:21:27 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

static void	swap_temp(t_data *data, char **line, char *temp)
{
	move_cursor_left(&data->pos, data->termkey->left);
	ft_putstr_fd(data->termkey->clear, 0);
	free(*line);
	*line = ft_strdup(temp);
	free(temp);
	write(0, *line, ft_strlen(*line));
	data->pos = ft_strlen(*line);
}

void	check_key_down(t_data *data, char **line)
{
	char	*temp;
	t_hist	*tmp;

	temp = NULL;
	tmp = data->hist_curr_down;
	if (!(*(data->hist)))
		return ;
	if (!tmp)
	{
		data->hist_curr_up = *(data->hist);
		temp = ft_strdup("");
	}
	else if (tmp)
	{
		data->hist_curr_up = data->hist_curr_down->next;
		temp = ft_strdup(tmp->cmd);
		data->hist_curr_down = data->hist_curr_down->prev;
	}
	swap_temp(data, line, temp);
}

char	*security_history_up(t_data *data)
{
	char	*temp;

	if (!*(data->hist) || !data->hist_curr_up)
		return (NULL);
	temp = NULL;
	if (data->hist_curr_up)
	{
		if (data->hist_curr_up->prev)
			data->hist_curr_down = data->hist_curr_up->prev;
		temp = ft_strdup(data->hist_curr_up->cmd);
		data->hist_curr_up = data->hist_curr_up->next;
	}
	return (temp);
}

void	check_key_up(t_data *data, char **line)
{
	char	*temp;

	temp = NULL;
	temp = security_history_up(data);
	if (!temp)
		return ;
	move_cursor_left(&data->pos, data->termkey->left);
	ft_putstr_fd(data->termkey->clear, 0);
	free(*line);
	*line = ft_strdup(temp);
	if (temp)
		free(temp);
	write(0, *line, ft_strlen(*line));
	data->pos = ft_strlen(*line);
}
