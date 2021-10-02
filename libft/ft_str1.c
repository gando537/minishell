/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:44:14 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/01 17:55:44 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char			*res;
	unsigned int	i;

    i = 0;
    res = malloc(sizeof(char) * (n + 1));
    if (res == NULL)
        return (NULL);
    while (s[i] && i < n)
    {
        res[i] = s[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

char	*ft_strdup(const char *src)
{
	int		size;
	char	*strdp;
	char	*p_strdp;

	size = 0;
	strdp = (char *)NULL;
	if (!src)
		return (strdp);
	while (src[size])
		size++;
	strdp = (char *) malloc(sizeof(char) * size + 1);
	if (!strdp)
		return (NULL);
	p_strdp = strdp;
	while (*src)
		*p_strdp++ = *src++;
	*p_strdp = '\0';
	return (strdp);
}