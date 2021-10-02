/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joker.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:09:38 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/01 17:56:33 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

char	*begend_str(char *sub_str, int i)
{
	DIR				*folder;
	char			*tmp;
	char			*tmp1;
	struct dirent	*entry;

	folder = opendir(".");
	entry = readdir(folder);
	tmp = ft_strdup("");
	while (entry)
	{
		tmp1 = joker_m(tmp, sub_str, entry, i);
		if (tmp1)
		{
			tmp = ft_strdup(tmp1);
			free(tmp1);
		}
		entry = readdir(folder);
	}
	closedir(folder);
	if (ft_strlen(tmp))
		return (tmp);
	free(tmp);
	return ((char *)NULL);
}

char	*parse_sub(char *sub_str)
{
	char	*str;

	str = (char *)NULL;
	if (ft_strlen(sub_str) == 1)
		return (joker_bis());
	if (*sub_str == '*')
	{
		str = begend_str(sub_str + 1, 0);
		return (str);
	}
	else if (ft_strlen(sub_str) >= 1 && sub_str[ft_strlen(sub_str) - 1] == '*')
	{
		sub_str[ft_strlen(sub_str) - 1] = '\0';
		str = begend_str(sub_str, 1);
		sub_str[ft_strlen(sub_str)] = '*';
		return (str);
	}
	return (str);
}


char	*joker(char *r, char *sub_str)
{
	char	*str;
	char	*new_str;

	str = parse_sub(sub_str);
	new_str = malloc(ft_strlen(r) + ft_strlen(str) + 1);
	new_str = ft_strcpy(new_str, r);
	if (str)
	{
		str_replace(new_str, sub_str, str);
		free(sub_str);
		free(str);
		free(r);
		return (new_str);
	}
	return ((char *)NULL);
}
