/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inidata_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:09:22 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/01 17:52:46 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	valid_red(char **cmd, t_data *data, char *tmp, int i)
{
	if (ft_strcmp(cmd[i],">") == 0)
	{
		data->o_fd = open(cmd[i + 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		str_replace(tmp, cmd[i + 1], "");
	}
	if (ft_strcmp(cmd[i],">>") == 0)
	{
		data->o_fd = open(cmd[i + 1], O_WRONLY | O_APPEND | O_CREAT, 0777);
		str_replace(tmp, cmd[i + 1], "");
	}
}

t_data	*alloc_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->last_exit = 0;
	data->o_fd = 1;
	data->i_fd = 0;
	data->pid_sh = ft_itoa(getppid());
	return (data);
}