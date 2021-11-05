/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 09:57:27 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/05 20:03:49 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	check_home(t_data *data, char *buf)
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 72)
	{
		move_cursor_left(&data->inter->pos, data->termkey->left);
	}
}

void	check_end(t_data *data, char *buf, char **line)
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 70)
	{
		while ((size_t)data->inter->pos < ft_strlen(*line))
		{
			ft_putstr_fd(data->termkey->right, 0);
			data->inter->pos += 1;
		}
	}
}

void	free_lst_cmd(t_cmd **lst)
{
	t_cmd	*tmp;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		if (tmp->cmd)
			ft_strdel(&tmp->cmd);
		tmp = tmp->next;
	}
	free(lst);
}

void	free_var(char *tmp, char *l)
{
	if (tmp)
		free(tmp);
	if (l)
		free(l);
}

char	*pop_redir(t_data *data, char **s, char *r, int i)
{
	char	*path;
	char	*tmp;

	path = (char *) NULL;
	delimiter(s, i, data, &path);
	data->inter->out = 0;
	if (ft_isinset('>', r))
		data->inter->out = 1;
	str_replace(r, s[i], "");
	if (!path)
	{
		tmp = malloc(sizeof(char) * ft_strlen(r) + 5);
		ft_strcpy(tmp, r);
		str_replace(tmp, s[i + 1], "cat");
		return (tmp);
	}
	else
		free(path);
	return (r);
}
