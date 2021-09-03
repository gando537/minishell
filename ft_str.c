/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 17:26:13 by mdiallo           #+#    #+#             */
/*   Updated: 2021/09/02 18:20:18 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	*ft_strncat(char *dest, char *src, int nb)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0' && j < nb)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

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