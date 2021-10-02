/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 09:57:27 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/01 17:53:05 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void    check_home(t_data *data, char *buf)
{
    if (buf[0] == 27 && buf[1] == 91 && buf[2] == 72)
    {
        move_cursor_left(&data->pos, data->termkey->left);
    }
}

void    check_end(t_data *data, char *buf, char **line)
{
    if (buf[0] == 27 && buf[1] == 91 && buf[2] == 70)
    {
        while ((size_t)data->pos < ft_strlen(*line))
        {
            ft_putstr_fd(data->termkey->right, 0);
            data->pos += 1;
        }
    }
}