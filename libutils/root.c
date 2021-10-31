/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:20:19 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/29 17:12:39 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libutils.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' \
			|| c == '\f' || c == '\n' || c == '\r');
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	size;
	char	*p_s1;
	char	*p_s2;
	char	*new_str;
	char	*p_new_str;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	p_s1 = s1;
	p_s2 = s2;
	p_new_str = new_str;
	while (p_s1 && *p_s1)
		*p_new_str++ = *p_s1++;
	while (p_s2 && *p_s2)
		*p_new_str++ = *p_s2++;
	*p_new_str = '\0';
	return (new_str);
}
