/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:28:23 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/29 17:12:39 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libutils.h"

int	replace_pip(char *s, int i)
{
	str_replace(s, "| ", "|");
	str_replace(s, " |", "|");
	str_replace(s, "|", " | ");
	i++;
	return (i);
}

void	replace_andor(char *s)
{
	str_replace(s, "|| ", "||");
	str_replace(s, " ||", "||");
	str_replace(s, "||", " || ");
	str_replace(s, "&& ", "&&");
	str_replace(s, " &&", "&&");
	str_replace(s, "&&", " && ");
}

char	*redirection(char *r)
{	
	char	*new_r;
	int		nb;
	int		i;

	nb = ft_nbre(r);
	new_r = ft_strndup(r, ft_strlen(r) + (nb * 2));
	i = 0;
	while (new_r[i])
	{
		if (new_r[i] == '<' && new_r[i + 1] != '<')
			i = replace_in(new_r, i);
		else if (new_r[i] == '>' && new_r[i + 1] != '>')
			i = replace_out(new_r, i);
		else if (new_r[i] == '<' && new_r[i + 1] == '<')
			i = replace_inin(new_r, i);
		else if (new_r[i] == '>' && new_r[i + 1] == '>')
			i = replace_outout(new_r, i);
		else if (new_r[i] == '|' && new_r[i + 1] != '|')
			i = replace_pip(new_r, i);
		i++;
	}
	return (new_r);
}
