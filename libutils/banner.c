/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 13:54:02 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/29 17:16:25 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libutils.h"

void	get_next_line_b(char **line, char *tmp, int l, char c)
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

int	get_next_l(char **line, int fd)
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
	while (r && l++ && c != '\n')
	{
		tmp = malloc(l);
		if (!tmp)
		{
			free(*line);
			return (-1);
		}
		get_next_line_b(line, tmp, l, c);
		r = read(fd, &c, 1);
	}
	return (r);
}

void	print_banner(void)
{
	int		fd;
	char	*filename;
	char	*read_str;

	filename = "image.txt";
	fd = open(filename, O_RDONLY);
	printf("\033[36m");
	while (get_next_l(&read_str, fd) > 0)
	{
		printf("%s\n", read_str);
		free(read_str);
	}
	printf("\033[00m");
	free(read_str);
}
