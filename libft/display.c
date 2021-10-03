/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:05:21 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/03 15:56:07 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	replace_escap(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' && s[i + 1] == ' ')
			str_replace(s, "  ", " ");
		i++;
	}
}

char	*clear_sc()
{
	const char	*clear;

	clear = "\e[1;1H\e[2J";
	write(1, clear, 11);
	return ((char *)NULL);
}

void    display_right(int i, char **line)
{
    char *s;

    s = *line;
    while (s[i])
    {
        write(0, s + i, 1);
        ++i;
    }
}
void    move_cursor_left(size_t *s, char *left)
{
    while (*s)
    {
        ft_putstr_fd(left, 0);
        *s -= 1;
    }
}

char	*display_prompt()
{
	char	path[255];
	char	*res;
	char	*res1;
	char	*res2;
	char	**rep;

	getcwd(path, 255);
	res = ft_strjoin("\033[34;01m➜ [\033[33m User@\033[035m", getenv("USER"));
	res1 = ft_strjoin(res, "\033[34;01m ]:\033[36m ");
	free(res);
	rep = ft_split(path, '/');
	if (ft_strcmp(path, "/") == 0)
		res2 = ft_strjoin(res1, "/");
	else if (ft_strcmp(getenv("USER"), rep[len_split(rep) - 1]) == 0)
		res2 = ft_strjoin(res1, "~");
	else
		res2 = ft_strjoin(res1, rep[len_split(rep) - 1]);
	res = ft_strjoin(res2, " $\033[00m ");
	free(res1);
	free(res2);
	free_split(rep);
	return(res);
}