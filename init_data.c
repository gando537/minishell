/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:06:15 by mdiallo           #+#    #+#             */
/*   Updated: 2021/01/01 02:31:40 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	search_str(char **tb, char *str)
{
	int	i;

	i = 0;
	while (tb[i])
		if (ft_strcmp(tb[i++], str) == 0)
			break ;
	if (ft_strcmp(tb[--i], str) != 0)
		return (0);
	return (i);
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

char	*input_file(char *r, char **cmd, t_data *data)
{
	char	*s;
	char	*tmp;
	size_t	len;

	data->in = 1;
	/*if (len_split(cmd) <= 1)
	{
		free_split(cmd);
		perror("minishell");
		exit(EXIT_FAILURE);
	}*/
	if (len_split(cmd) <= 1)
		return (r);
	s = r;
	while (*s != '<')
		s++;
	len = ft_strlen(cmd[1]) + 3;
	data->i_fd = open(cmd[1], O_RDONLY);
	tmp = s + len;
	return (tmp);
}

char	*output_file(char **cmd, t_data *data, char *tmp)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		/*if ((ft_strcmp(cmd[i],">") == 0 || ft_strcmp(cmd[i],">>") == 0)
			&& cmd[i + 1] == NULL)
		{
			free_split(cmd);
			perror("minishell");
			exit(EXIT_FAILURE);
		}*/
		if ((ft_strcmp(cmd[i], ">") == 0 || ft_strcmp(cmd[i], ">>") == 0)
			&& cmd[i + 1] != NULL)
			valid_red(cmd, data, tmp, i);
		i++;
	}
	return (tmp);
}

void	init_data(t_data *data, char *r)
{
	char	**cmd;
	char	*tmp;

	tmp = r;
	if (ft_strlen(r) == 0)
		return ;
	cmd = ft_split(r, ' ');
	data->in = 0;
	if (ft_strcmp(cmd[0], "<") == 0 || ft_strcmp(cmd[0], "<<") == 0)
		tmp = input_file(r, cmd, data);
	data->o_fd = 1;
	if (search_str(cmd, ">") || search_str(cmd, ">>"))
		tmp = output_file(cmd, data, tmp);
	data->pip = ft_split(tmp, '|');
	data->nb_pipes = len_split(data->pip) - 1;
	data->my_pipes = creat_pipe(data->nb_pipes);
	data->j = 0;
	free_split(cmd);
}
