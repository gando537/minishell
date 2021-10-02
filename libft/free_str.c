/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:44:24 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/01 20:09:26 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	ft_isinset(int c, char *set)
{
	size_t i;

	i = 0;
	if (!c)
		return (0);
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		++i;
	}
	return (0);
}

void	search_c(char *s)
{
	int	i;

	i = 1;
	if (ft_strlen(s) == 1)
		return ;
	while (s[i] && s[i] != ' ')
		i++;
	if (s[--i] == '*')
		s[i] = ' ';
}

int	len_split(char **split)
{
	int	i;
	int	j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
			j++;
		i++;
	}
	return (i);
}

void	free_split(char **split)
{
	int	len;
	int	i;

	if (!*split || !split)
		return ;
	i = 0;
	len = len_split(split);
	while (i < len)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_strdel(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = NULL;
	}
}
