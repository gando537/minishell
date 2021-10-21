/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:16:43 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/13 07:24:53 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

char	*new_str(t_data *data, char *cmd_split, char *ech)
{
	char	*tmp;
	char	*new_s;
	char	*s;
	char	*s_nul;

	s = (char *) NULL;
	s_nul = (char *) NULL;
	new_s = (char *) NULL;
	tmp = ft_strjoin(ech, " ");
	free(ech);
	if (cmd_split[1] == '$' || cmd_split[1] == '?')
		return (new_str_bis(data, cmd_split, tmp, s_nul));
	s = _var_mp(data, cmd_split + 1);
	if (s)
		new_s = ft_strjoin(tmp, s);
	else
		new_s = ft_strjoin(tmp, cmd_split);
	free(tmp);
	return (new_s);
}

char	*ft_substr(char *str, char c)
{
	int		i;
	int		j;
	char	*sub_str;

	i = 0;
	sub_str = malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == c)
		{
			j = -1;
			while (str[i] && str[i] != ' ')
				sub_str[++j] = str[i++];
			sub_str[++j] = '\0';
			return (sub_str);
		}
		i++;
	}
	return ((char *) NULL);
}

char	*_variable_(t_data *data, char *cmd_split, char *ech)
{
	char	*new_s;
	char	*tmp;

	new_s = (char *) NULL;
	if (cmd_split[0] == '$' && ft_strlen(cmd_split) > 1)
		new_s = new_str(data, cmd_split, ech);
	else
	{
		tmp = ft_strjoin(ech, " ");
		free(ech);
		new_s = ft_strjoin(tmp, cmd_split);
		free(tmp);
	}
	return (new_s);
}

char	*gestion_var(t_data *data, char **cmd_split)
{
	int		i;
	char	*ech;

	i = 1;
	ech = ft_strdup(cmd_split[0]);
	if (ft_strcmp(cmd_split[1], "-n") == 0)
		i++;
	while (cmd_split[i])
		ech = _variable_(data, cmd_split[i++], ech);
	return (ech);
}
