/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:35:57 by mdiallo           #+#    #+#             */
/*   Updated: 2021/01/01 02:56:38 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	builtin_pwd_echo(t_data *data, char **cmd_split, char *r)
{
	if (ft_strcmp(cmd_split[0], "pwd") == 0)
		data->last_exit = builtin_pwd();
	else if (ft_strcmp(cmd_split[0], "echo") == 0)
	{
		data->last_exit = 0;
		if (check_echo(data, cmd_split))
			return ;
		replace_escap(r);
		if (ft_strcmp(cmd_split[1], "-n") == 0)
			write(data->o_fd, r + 9, ft_strlen(r + 9));
		else
		{
			write(data->o_fd, r + 5, ft_strlen(r + 5));
			write(data->o_fd, "\n", 1);
		}
		data->o_fd = 1;
	}
}

int	checker_builti(char *r, char **cmd_split, t_data *data)
{
	if (ft_strcmp(cmd_split[0], "cd") == 0)
	{
		data->last_exit = ft_chdir(r);
		free_split(cmd_split);
		return (1);
	}
	if (ft_strcmp(cmd_split[0], "pwd") == 0
		|| ft_strcmp(cmd_split[0], "echo") == 0)
	{
		builtin_pwd_echo(data, cmd_split, r);
		free_split(cmd_split);
		return (1);
	}
	if (ft_strcmp(cmd_split[0], "env") == 0)
	{
		printer_env(data->listenv);
		data->last_exit = 0;
		free_split(cmd_split);
		return (1);
	}
	return (0);
}

int	builti_bis_(t_data *data, char **split)
{
	if (search_vari(data, split))
	{
		free_split(split);
		return (1);
	}
	if (ft_strcmp(split[0], "export") == 0)
	{
		if (split[1])
			gand(split[1], data);
		free_split(split);
		return (1);
	}
	if (ft_strcmp(split[0], "unset") == 0)
	{
		if (split[1])
			pop_var(data->listenv, split[1]);
		free_split(split);
		return (1);
	}
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
