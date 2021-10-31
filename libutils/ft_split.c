/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:59:43 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/29 17:12:39 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libutils.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (len);
	while (str[len])
		len++;
	return (len);
}

static int	r_size(char *s, char c)
{
	unsigned int	len;

	len = 0;
	while (*s)
	{
		if (*s == c)
			++s;
		else
		{
			++len;
			while (*s && *s != c)
				++s;
		}
	}
	return (len);
}

static t_ind	*allocated(void)
{
	t_ind	*ind;

	ind = malloc(sizeof(t_ind));
	if (!ind)
		return (NULL);
	ind->i = 0;
	ind->j = 0;
	ind->w_len = 0;
	return (ind);
}

static void	split_bis(t_ind *ind, char *s, char **r, char c)
{
	while (s[ind->i] && s[ind->i] == c)
		ind->i += 1;
	while (s[ind->i] && s[ind->i] != c)
	{
		ind->w_len += 1;
		ind->i += 1;
	}
	r[ind->j] = (char *)malloc(sizeof(char) * (ind->w_len + 1));
	if (!r[ind->j])
		return ;
}

char	**ft_split(char *s, char c)
{
	t_ind	*ind;
	int		k;
	char	**r;

	ind = allocated();
	r = (char **)malloc(sizeof(char *) * (r_size(s, c) + 1));
	if (!r)
		return (0);
	while (s[ind->i] && ind->j < r_size(s, c))
	{
		split_bis(ind, s, r, c);
		k = 0;
		while (ind->w_len)
		{
			r[ind->j][k++] = s[ind->i - ind->w_len];
			ind->w_len -= 1;
		}
		r[ind->j][k] = '\0';
		ind->j++;
	}
	r[ind->j] = (void *)0;
	free(ind);
	return (r);
}
