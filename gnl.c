/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:20:24 by mdiallo           #+#    #+#             */
/*   Updated: 2021/01/01 02:00:53 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

static void	write_fd(t_gnl gnl)
{
	if (gnl.buf)
		write(0, gnl.buf, 1);
}

int	press_keys(t_gnl gnl, t_data *data, char **line)
{
	int	i;

	if (cheker_keys(gnl))
	{
		if (gnl.buf[0] == 127)
		{
			trm_backspace(data, line, gnl);
			return (1);
		}
		i = fctn_ctrl(gnl, data, line);
		if (i == 2)
			return (i);
		execute_key(data, gnl, line);
		return (1);
	}
	return (0);
}

int	checker_ctrl(t_gnl gnl, t_data *data, char **line)
{
	int		i;

	i = press_keys(gnl, data, line);
	if (!i)
	{
		write_fd(gnl);
		return (1);
	}
	else if (i == 2)
	{
		free(gnl.buf);
		return (0);
	}
	return (2);
}

void	re_init(t_data *data, t_gnl gnl)
{
	free(gnl.buf);
	data->hist_curr_up = *(data->hist);
	data->hist_curr_down = NULL;
}

void	gnl_term(char **line, int fd, t_data *data)
{
	t_gnl	gnl;

	gnl.r = 0;
	gnl.l = 1;
	*line = malloc(gnl.l);
	gnl.buf = malloc(sizeof(char) * 3 + 1);
	(*line)[0] = 0;
	data->pos = 0;
	gnl.r = read(fd, gnl.buf, 3);
	if (!checker_ctrl(gnl, data, line))
		return ;
	while (gnl.r && gnl.buf[0] != '\n')
	{
		if (!cheker_keys(gnl))
		{
			gnl.l++;
			gnl_term_bis(line, gnl, data);
		}
		gnl.r = read(fd, gnl.buf, 3);
		if (!checker_ctrl(gnl, data, line))
			return ;
	}
	re_init(data, gnl);
}
