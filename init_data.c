/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:06:15 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/05 15:46:15 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	search_str(char **tb, char *str)
{
	int	i;

	i = -1;
	while (tb[++i])
		if (ft_strcmp(tb[i], str) == 0)
			return (1);
	return (0);
}

int	check_file_exist(const char *filename)
{
	struct stat	buffer;
	int			exist;

	exist = stat(filename, &buffer);
	if (exist == 0)
		return (1);
	return (0);
}

void	input_file(char **cmd, t_data *data)
{
	int		i;

	data->inter->in = 1;
	if (len_split(cmd) <= 1)
		return ;
	i = 0;
	while (cmd[i] && ft_strcmp(cmd[i], "<"))
		++i;
	if (cmd[i] && cmd[i + 1])
		data->inter->i_fd = open(cmd[i + 1], O_RDONLY);
}

void	output_file(char **cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if ((ft_strcmp(cmd[i], ">") == 0 || ft_strcmp(cmd[i], ">>") == 0)
			&& cmd[i + 1] != NULL)
			valid_red(cmd, data, i);
		i++;
	}
}

void	init_data(t_data *data, char *r)
{
	char	**cmd;

	if (ft_strlen(r) == 0)
		return ;
	cmd = ft_split(r, ' ');
	data->inter->in = 0;
	if (search_str(cmd, "<"))
		input_file(cmd, data);
	data->inter->o_fd = 1;
	if (search_str(cmd, ">") || search_str(cmd, ">>"))
		output_file(cmd, data);
	data->pip = ft_split(r, '|');
	data->inter->nb_pipes = len_split(data->pip) - 1;
	data->inter->n = data->inter->nb_pipes;
	data->my_pipes = creat_pipe(data->inter->nb_pipes);
	data->inter->j = 0;
	data->tmp = (char *) NULL;
	free_split(cmd);
	free_split(data->pip);
}
