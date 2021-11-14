/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:57:59 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/14 14:42:55 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libutils.h"

size_t	get_non_escaped(char *str, size_t i, char *sep)
{
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	while (str[i])
	{
		if (str[i] == '"' && (i == 0 || str[i - 1] != '\\')
			&& dq == 0 && sq == 0)
			++dq;
		else if (str[i] == '"' && (i == 0 || str[i - 1] != '\\') && dq == 1)
			--dq;
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\')
			&& sq == 0 && dq == 0)
			++sq;
		else if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\') && sq == 1)
			--sq;
		if (ft_isinset(str[i], sep) && (i == 0 || str[i - 1] != '\\')
			&& sq == 0 && dq == 0)
			return (i);
		++i;
	}
	return (i);
}

int	is_first_char(char *str, char *set)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	if (ft_isinset(str[i], set))
		return (1);
	return (0);
}

int	is_last_char(char *str, char *set)
{
	size_t	i;

	i = ft_strlen(str) - 1;
	while (ft_isspace(str[i]))
		--i;
	if (ft_isinset(str[i], set) && (i == 0 || str[i - 1] != '\\'))
		return (1);
	return (0);
}

size_t	find_char(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		++i;
	return (i);
}

int	is_builtin(char	*str)
{
	if (!ft_strcmp(str, "exit") || \
		!ft_strcmp(str, "pwd") || \
		!ft_strcmp(str, "cd") || \
		!ft_strcmp(str, "echo") || \
		!ft_strcmp(str, "export") || \
		!ft_strcmp(str, "unset"))
		return (1);
	return (0);
}
