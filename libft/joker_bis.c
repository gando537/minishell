/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joker_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 12:51:39 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/09 00:33:15 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

char	*ft_pos(char *name, char *sub_str)
{
	char	*s;
	size_t	n;

	if (*name == '.' || ft_strlen(sub_str) > ft_strlen(name))
		return (0);
	s = name + ft_strlen(name);
	n = ft_strlen(sub_str);
	while (n--)
		--s;
	return (s);
}

char	*replik_j(char *str, char *name)
{
	char	*tmp;
	char	*tmp1;

	tmp = str;
	tmp1 = ft_strjoin(tmp, " ");
	str = ft_strjoin(tmp1, name);
	free(tmp1);
	free(tmp);
	return (str);
}

char	*joker_m(char *str, char *sub_str, struct dirent *entry, int i)
{
	char	*s;

	s = (char *) NULL;
	if (i == 0)
	{
		s = ft_pos(entry->d_name, sub_str);
		if (!s || ft_strcmp(s, sub_str))
			return ((char *) NULL);
	}
	else
	{
		if (ft_strncmp(entry->d_name, sub_str, ft_strlen(sub_str)))
			return ((char *) NULL);
	}
	return (replik_j(str, entry->d_name));
}

char	*joker_bis(void)
{
	char			*tmp;
	char			*s;
	DIR				*folder;
	struct dirent	*entry;

	folder = opendir(".");
	entry = readdir(folder);
	while (entry)
	{
		if (*(entry->d_name) != '.' )
		{
			if (!s)
				tmp = ft_strdup(entry->d_name);
			else
			{
				tmp = ft_strjoin(s, " ");
				s = ft_strjoin(tmp, entry->d_name);
				free(tmp);
			}
		}
		entry = readdir(folder);
	}
	closedir(folder);
	return (s);
}
