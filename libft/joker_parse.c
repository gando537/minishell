/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joker_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:22:46 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/01 20:33:11 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	strcpy_no_quotes(char *s1, char *s2)
{
	int	i;
    int	j;
    int	flag;

	i = -1;
	j = 0;
	flag = -1;
	while (s1[++i])
	{
		if (flag == -1 && ft_isinset(s1[i], "\"\'") && 
			(i == 0 || s1[i - 1] != '\\'))
			flag = i;
		else if (flag != -1 && s1[flag] == s1[i] &&
			(s1[i - 1] != '\\' || s1[flag] == '\''))
			flag = -1;
		else
		{
			if (s1[i] == '\\' && (flag == -1 ||
				(s1[flag] == '"' && ft_isinset(s1[i + 1], "$\"\\"))))
				++i;
			s2[j++] = s1[i];
			s1[i] = '\0';
		}
	}
	s2[j] = '\0';
}

char	*replace_pipe(char *s)
{
	char	*tmp;

	tmp = ft_strjoin(s, "|");
	free(s);
	return (tmp);
}

char	*rm_quotes(char *cmd)
{
	int		i;
	char	**split;
	char	*str;
	char	*new_str;
	char	*tmp;

	i = 0;
	new_str = (char *)NULL;
	split = ft_split(cmd, '|');
	while (split[i])
	{
		str = malloc(ft_strlen(split[i]) + 3);
		strcpy_no_quotes(split[i], str);
		if (split[i + 1])
			str = replace_pipe(str);
		tmp = new_str;
		new_str = ft_strjoin(new_str, str);
		free(tmp);
		free(str);
		i++;
	}
	free_split(split);
	return (new_str);
}