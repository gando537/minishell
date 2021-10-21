/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_left_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 09:55:09 by mdiallo           #+#    #+#             */
/*   Updated: 2021/01/01 01:30:32 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	check_key_left(t_data *data)
{
	if (data->inter->pos == 0)
		return ;
	ft_putstr_fd(data->termkey->left, 0);
	data->inter->pos--;
}

void	check_key_right(t_data *data, char *buf, char **line)
{
	if (!*line || data->inter->pos == ft_strlen(*line))
		return ;
	write(0, buf, 3);
	data->inter->pos++;
}

int	print_error(void)
{
	write(2, "minishell: syntax error\n", 25);
	return (0);
}
