/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:52:42 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/01 17:53:58 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	check_curr(char *str, int curr, char *s)
{
	if (curr == 0) 
		curr = get_non_escaped(str, curr, s);
	return (curr);
}

static int	valid_pipes(char *str)
{
	size_t	i;
	size_t	curr;

	if (is_first_char(str, "|") || is_last_char(str, "|"))
		return (print_error());
	curr = 0;
	while (curr == 0 || str[curr])
	{
		curr = check_curr(str, curr, "|");
		if (!str[curr])
			break ;
		i = curr + 1;
		while (ft_isspace(str[i]))
			++i;
		if (ft_isinset(str[i], "|;"))
			return (print_error());
		curr = get_non_escaped(str, curr + 1, "|");
	}
	return (1);
}

static int	valid_redirect(char *str)
{
	size_t	i;
	size_t	curr;

	if (is_last_char(str, "<>"))
		return (print_error());
	curr = 0;
	while (curr == 0 || str[curr])
	{
		curr = check_curr(str, curr, "<>");
		if (!str[curr])
			break ;
		i = curr + 1;
		if ((ft_isinset(str[i], "<>") && str[i] != str[curr]) || !str[i])
			return (print_error());
		if (str[i] == str[curr])
			++i;
		while (ft_isspace(str[i]))
			++i;
		if (ft_isinset(str[i], "<>;|"))
			return (print_error());
		curr = get_non_escaped(str, curr + 1, "<>");
	}
	return (1);
}

static int	valid_semicolon(char *str)
{
	size_t	i;
	size_t	curr;

	if (is_first_char(str, ";"))
		return (print_error());
	curr = 0;
	while (curr == 0 || str[curr])
	{
		curr = check_curr(str, curr, ";");
		if (!str[curr])
			break ;
		i = curr + 1;
		while (ft_isspace(str[i]))
			++i;
		if (ft_isinset(str[i], ";|"))
			return (print_error());
		curr = get_non_escaped(str, curr + 1, ";");
	}
	return (1);
}

int	valid_syntax(char *line)
{
	if (!line[0])
		return (1);
	if (!valid_pipes(line) || !valid_redirect(line) || !valid_semicolon(line))
		return (0);
	return (1);
}
