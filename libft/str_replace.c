/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 17:24:09 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/01 17:56:51 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	search_char(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		if (s[i++] == c)
			return (1);
	return (0);	
}

int	nbr_bis(char *str, int i, int nbre)
{
	while (str[i])
    {
		if (str[i] == '<' && str[i + 1] == '<')
		{
			i++;
			++nbre;
		}
		else if (str[i] == '<')
			++nbre;
		else if (str[i] == '>' && str[i + 1] == '>')
		{
			i++;
			++nbre;
        }
		else if (str[i] == '>')
			++nbre;
		else if (str[i] == '|')
			++nbre;
		i++;
	}
	return (nbre);
}

int	ft_nbre(char *str)
{
	int	nbre;
	int	i;

	i = 0;
	nbre = 0;
	nbre = nbr_bis(str, i, nbre);
	return (nbre);
}

void	str_replace_bis(char *str, char *rech, char *remp, int nbre)
{
	char	*p;
	char	*tmp;
	char	*str_cpy;

	str_cpy = malloc(ft_strlen(str) - \
	(ft_strlen(rech) * nbre) + (ft_strlen(remp) * nbre) + 1);
	str_cpy[0] = '\0';
	p = str;
	tmp = ft_strstr(p,rech);
	while (tmp != NULL)
	{
		ft_strncat(str_cpy, p, tmp - p);
		ft_strcat(str_cpy, remp);
		p = tmp + ft_strlen(rech);
		tmp = ft_strstr(p, rech);
	}
	ft_strcat(str_cpy, p);
	ft_strcpy(str, str_cpy);
	free(str_cpy);
}

void	str_replace(char *str, char *rech, char *remp)
{
	int		nbre;
	char	*p;
	char	*tmp;
    
	nbre = 0;
	p = str;
	tmp = ft_strstr(p,rech);
	while (tmp != NULL)
	{
		++nbre;
		p = tmp + ft_strlen(rech);
		tmp = ft_strstr(p, rech);
	}
	if (nbre > 0)
		str_replace_bis(str, rech, remp, nbre);
}
