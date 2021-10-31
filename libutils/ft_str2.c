/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:44:18 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/29 17:12:39 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libutils.h"

char	*substr(char *str)
{
	int		j;
	char	**sp;

	j = -1;
	sp = ft_split(str, ' ');
	while (sp[++j])
		if (search_char(sp[j], '*'))
			return (ft_strdup(sp[j]));
	return (0);
}

void	ft_cpy(char *beg, char *end, char *src)
{
	int	i;
	int	j;

	i = -1;
	while (src[++i] != '*')
		beg[i] = src[i];
	beg[i] = '*';
	beg[++i] = '\0';
	j = 0;
	while (src[i])
		end[j++] = src[i++];
	end[j] = '\0';
}

int	ft_strstr_bis(char *str, char *to_find)
{
	char	*s;

	s = ft_pos(str, to_find);
	if (!s || ft_strcmp(s, to_find))
		return (0);
	return (1);
}

char	*reduce_mm(char *new_s, char *spi)
{
	char	*tmp;

	tmp = new_s;
	if (tmp)
	{
		new_s = ft_strjoin(new_s, " ");
		free(tmp);
	}
	tmp = new_s;
	new_s = ft_strjoin(new_s, spi);
	if (tmp)
		free(tmp);
	return (new_s);
}

char	*reduce_m(char **sp, char *end)
{
	int		i;
	char	*new_s;

	i = -1;
	new_s = (char *) NULL;
	while (sp[++i])
	{
		if (ft_strlen(sp[i]) < ft_strlen(end))
			continue ;
		if (ft_strstr_bis(sp[i], end))
			new_s = reduce_mm(new_s, sp[i]);
	}
	return (new_s);
}
