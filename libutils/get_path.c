/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 20:29:42 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/29 17:12:39 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libutils.h"

char	*search_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*part_path;

	i = 0;
	while (paths[i] && cmd[1] != '/')
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		ft_strdel(&part_path);
		if (check_file_exist(path))
			return (path);
		ft_strdel(&path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd)
{
	char	**paths;
	char	*envp;
	char	*pth;

	envp = getenv("PATH");
	paths = ft_split(envp, ':');
	pth = search_path(paths, cmd);
	free_split(paths);
	return (pth);
}

char	*parse_r(char *r)
{
	char	*p_r;
	char	*tmp;

	tmp = r;
	while (*tmp != '\0')
	{
		if (ft_isspace(*tmp))
		{
			p_r = tmp;
			while (ft_isspace(*tmp))
			{
				tmp++;
				if (*tmp == '\0')
					*p_r = '\0';
			}
		}
		else
			tmp++;
	}
	return (r);
}

char	*stripwhite(char *string)
{
	char	*s;
	char	*t;

	s = string;
	while (ft_isspace(*s))
		s++;
	if (*s == 0)
		return (s);
	t = s + ft_strlen (s) - 1;
	while (t > s && ft_isspace (*t))
		t--;
	*++t = '\0';
	return (s);
}

int	checker_path(char *p_r)
{
	if (opendir(p_r) == NULL)
	{
		perror(p_r);
		return (1);
	}
	chdir(p_r);
	return (0);
}
