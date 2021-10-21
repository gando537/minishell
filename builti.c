/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:35:57 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/21 11:32:26 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	builtin_pwd_echo(t_data *data, char **cmd_split, char *r)
{
	int	fd;

	if (ft_strcmp(cmd_split[0], "pwd") == 0)
		data->inter->last_exit= builtin_pwd();
	else if (ft_strcmp(cmd_split[0], "echo") == 0)
	{
		data->inter->last_exit= 0;
		if (check_echo(data, cmd_split))
			return ;
		replace_escap(r);
		if (data->inter->nb_pipes&& data->inter->n)
			fd = data->my_pipes[data->inter->j + 1];
		else
			fd = data->inter->o_fd;
		if (ft_strcmp(cmd_split[1], "-n") != 0)
		{
			write(fd, r + 5, ft_strlen(r + 5));
			write(fd, "\n", 1);
		}
		else
			write(fd, r + 8, ft_strlen(r + 8));
		data->inter->o_fd= 1;
	}
}

int	checker_builti(char *r, char **cmd_split, t_data *data)
{
	if (ft_strcmp(cmd_split[0], "cd") == 0)
	{
		data->inter->last_exit= ft_chdir(r);
		return (1);
	}
	if (ft_strcmp(cmd_split[0], "pwd") == 0
		|| ft_strcmp(cmd_split[0], "echo") == 0)
	{
		builtin_pwd_echo(data, cmd_split, r);
		return (1);
	}
	if (ft_strcmp(cmd_split[0], "env") == 0)
	{
		printer_env(data->listenv);
		data->inter->last_exit= 0;
		return (1);
	}
	return (0);
}

int	builti_bis_(t_data *data, char **split)
{
	data->inter->b= 1;
	if (ft_strcmp(split[0], "export") == 0)
	{
		if (split[1])
			gand(split[1], data);
		return (1);
	}
	if (search_vari(data, split))
	{
		data->inter->b= 2;
		return (1);
	}
	if (ft_strcmp(split[0], "unset") == 0)
	{
		if (split[1])
			pop_var(data->listenv, split[1]);
		return (1);
	}
	data->inter->b= 0;
	return (0);
}

char	*dup_key(char *buf)
{
	char	*dst;

	dst = malloc(sizeof(*dst) * 4);
	if (!dst)
		return (NULL);
	dst[0] = '\0';
	free(buf);
	return (dst);
}
