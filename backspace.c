/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backspace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:54:49 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/24 13:54:44 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

static void	loop_cut_characters(int s, char *dst, char *tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (i != s)
		{
			dst[j] = tmp[i];
			++j;
		}
		++i;
	}
	dst[j] = '\0';
}

static int	cut_characters(t_data *data, char **line)
{
	char	*dst;
	char	*tmp;

	tmp = *line;
	dst = malloc(sizeof(*dst) * ft_strlen(tmp) + 1);
	if (!dst)
		return (0);
	loop_cut_characters(data->inter->pos - 1, dst, tmp);
	free(tmp);
	*line = dst;
	return (1);
}

void	trm_backspace(t_data *data, char **line, t_gnl gnl)
{
	if (data->inter->pos == 0)
		return ;
	gnl.l--;
	ft_putstr_fd(data->termkey->left, 0);
	ft_putstr_fd(data->termkey->save, 0);
	ft_putstr_fd(data->termkey->clear, 0);
	if (cut_characters(data, line) == 0)
	{
		write(2, "minishell: malloc: Error\n", 25);
		exit(EXIT_FAILURE);
	}
	display_right(data->inter->pos - 1, line);
	ft_putstr_fd(data->termkey->reset, 0);
	data->inter->pos--;
}
