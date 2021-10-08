/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 20:15:49 by mdiallo           #+#    #+#             */
/*   Updated: 2021/01/01 02:39:00 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	cheker_keys(t_gnl gnl)
{
	if ((gnl.buf[0] == 127) || (gnl.buf[0] == 12) || (gnl.buf[0] == 3) || \
		(gnl.buf[0] == 27 && gnl.buf[1] == 91 && gnl.buf[2] == 65) || \
		(gnl.buf[0] == 27 && gnl.buf[1] == 91 && gnl.buf[2] == 66) || \
		(gnl.buf[0] == 27 && gnl.buf[1] == 91 && gnl.buf[2] == 67) || \
		(gnl.buf[0] == 27 && gnl.buf[1] == 91 && gnl.buf[2] == 68) || \
		(gnl.buf[0] == 27 && gnl.buf[1] == 91 && gnl.buf[2] == 70) || \
		(gnl.buf[0] == 27 && gnl.buf[1] == 91 && gnl.buf[2] == 72) || \
		(gnl.buf[0] == 4) || (gnl.buf[0] == 9))
		return (1);
	return (0);
}

void	execute_key(t_data *data, t_gnl gnl, char **line)
{
	if (gnl.buf[0] == 27 && gnl.buf[1] == 91 && gnl.buf[2] == 65)
		check_key_up(data, line);
	if (gnl.buf[0] == 27 && gnl.buf[1] == 91 && gnl.buf[2] == 66)
		check_key_down(data, line);
	if (gnl.buf[0] == 27 && gnl.buf[1] == 91 && gnl.buf[2] == 67)
		check_key_right(data, gnl.buf, line);
	if (gnl.buf[0] == 27 && gnl.buf[1] == 91 && gnl.buf[2] == 68)
		check_key_left(data);
	if (gnl.buf[0] == 27 && gnl.buf[1] == 91 && gnl.buf[2] == 70)
		check_end(data, gnl.buf, line);
	if (gnl.buf[0] == 27 && gnl.buf[1] == 91 && gnl.buf[2] == 72)
		check_home(data, gnl.buf);
}

void	loop_insert_char(int pos, char *dst, char *tmp, t_gnl gnl)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (j == pos)
			dst[j++] = gnl.buf[0];
		else
			dst[j++] = tmp[i++];
	}
	dst[j] = '\0';
}

void	insert_char(t_data *data, char **line, t_gnl gnl)
{
	char	*dst;
	char	*tmp;
	size_t	pos;

	tmp = *line;
	pos = data->pos;
	dst = malloc(sizeof(*dst) * ft_strlen(tmp) + 2);
	if (!dst)
		return ;
	loop_insert_char(data->pos, dst, tmp, gnl);
	free(tmp);
	*line = dst;
	display_right(data->pos + 1, line);
	data->pos = ft_strlen(*line);
	while (data->pos-- > pos + 1)
		ft_putstr_fd(data->termkey->left, 0);
}

void	gnl_term_bis(char **line, t_gnl gnl, t_data *data)
{
	int		i;
	char	*tmp;

	i = -1;
	if (data->pos == ft_strlen(*line))
	{
		if (*line)
			gnl.l = ft_strlen(*line) + 2;
		tmp = malloc(gnl.l);
		while (++i < gnl.l - 2 && (*line)[i])
			tmp[i] = (*line)[i];
		tmp[i] = gnl.buf[0];
		tmp[i + 1] = 0;
		gnl.buf[0] = '\0';
		free(*line);
		*line = tmp;
	}
	else
		insert_char(data, line, gnl);
	data->pos++;
}
