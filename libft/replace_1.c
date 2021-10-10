/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:28:18 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/09 17:49:01 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	check_redir(char *r)
{
	if (ft_strstr(r, "<")
		|| ft_strstr(r, ">")
		|| ft_strstr(r, "<<")
		|| ft_strstr(r, ">>"))
		return (1);
	return (0);
}

int	replace_in(char *s, int i)
{
	str_replace(s, "< ", "<");
	str_replace(s, " <", "<");
	str_replace(s, "<", " < ");
	i++;
	return (i);
}

int	replace_inin(char *s, int i)
{
	str_replace(s, "<< ", "<<");
	str_replace(s, " <<", "<<");
	str_replace(s, "<<", " << ");
	i += 2;
	return (i);
}

int	replace_out(char *s, int i)
{
	str_replace(s, "> ", ">");
	str_replace(s, " >", ">");
	str_replace(s, ">", " > ");
	i++;
	return (i);
}

int	replace_outout(char *s, int i)
{
	str_replace(s, ">> ", ">>");
	str_replace(s, " >>", ">>");
	str_replace(s, ">>", " >> ");
	i += 2;
	return (i);
}
