/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inidata_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:09:22 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/05 17:48:19 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	get_next_line_bis(char **line, char *tmp, int l, char c)
{
	int		i;

	i = -1;
	while (++i < l - 2)
		tmp[i] = (*line)[i];
	tmp[i] = c;
	tmp[i + 1] = 0;
	free(*line);
	*line = tmp;
}

int	get_next_line(char **line, int fd)
{
	int		l;
	int		r;
	char	c;
	char	*tmp;

	r = 0;
	l = 1;
	*line = malloc(l);
	if (!*line)
		return (-1);
	(*line)[0] = 0;
	r = read(fd, &c, 1);
	write_fd(&c);
	while (r && l++ && c != '\n')
	{
		tmp = malloc(l);
		get_next_line_bis(line, tmp, l, c);
		r = read(fd, &c, 1);
		write_fd(&c);
	}
	return (r);
}

void	valid_red(char **cmd, t_data *data, int i)
{
	if (ft_strcmp(cmd[i], ">") == 0)
		data->inter->o_fd = open(cmd[i + 1], \
			O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (ft_strcmp(cmd[i], ">>") == 0)
		data->inter->o_fd = open(cmd[i + 1], \
			O_WRONLY | O_APPEND | O_CREAT, 0777);
}

t_data	*alloc_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->inter = (t_int *)malloc(sizeof(t_int));
	data->inter->last_exit = 0;
	data->inter->o_fd = 1;
	data->inter->i_fd = 0;
	data->pid_sh = ft_itoa(getppid());
	return (data);
}

void	limiter(t_data *data)
{
	char	*readop;
	int		r;

	data->inter->in = 1;
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		r = get_next_line(&readop, 0);
		if (ft_strcmp(data->limiter, readop) == 0 && ft_strlen(readop) != 0)
		{
			free(readop);
			close(data->inter->i_fd);
			return ;
		}
		ft_putendl_fd(readop, data->inter->i_fd);
		free(readop);
	}
}
