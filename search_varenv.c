/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_varenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:14:27 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/27 20:34:24 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

size_t	len_variable(char *str)
{
	size_t	n;

	n = 0;
	while (str[n] && str[n] != ' ')
		++n;
	return (n);
}

char	*_var_mp(t_data *data, char *var, int t)
{
	t_listenv	*tmp;

	if (t)
	{
		tmp = *(data->listenv);
		while (tmp)
		{
			if (ft_strcmp(tmp->name, var) == 0)
				return (tmp->value);
			tmp = tmp->next;
		}
	}
	tmp = *(data->var_tmp);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return ((char *) NULL);
}

char	*new_str_bis(t_data *data, char *cmd_split, char *tmp, char *s_nul)
{
	char	*s;
	char	*tmp1;

	s = (char *) NULL;
	tmp1 = (char *) NULL;
	if (cmd_split[1] == '$')
	{
		tmp1 = ft_strjoin(tmp, data->pid_sh);
		free(tmp);
		s = _var_mp(data, cmd_split + 2, 1);
		if (!s)
			return (ft_strjoin(tmp1, cmd_split + 2));
	}
	else if (cmd_split[1] == '?')
	{
		s_nul = ft_itoa(data->inter->last_exit);
		tmp1 = ft_strjoin(tmp, s_nul);
		free(tmp);
		free(s_nul);
		s = _var_mp(data, cmd_split + 2, 1);
		if (!s)
			return (ft_strjoin(tmp1, cmd_split + 2));
	}
	return (ft_strjoin(tmp1, s));
}

char	*reduce(t_data *data, char *str, int i)
{
	char	*var;

	var = (char *) NULL;
	if (str[i] == '*')
	{
		if (str[i + 1] && str[i + 1] != ' ' && str[i - 1] != ' ')
			return (reduce_bis(data, str));
		search_c(&str[i]);
		var = parse_jok(str, i);
		data->sub_str = ft_strdup(var);
		if (!var)
			return (0);
		str = joker(str, var);
		if (!str)
			return (0);
		free(data->sub_str);
	}
	return (str);
}

char	*joker_quotes(t_data *data, char *cmd)
{
	int		i;
	char	*str;

	str = rm_quotes(cmd);
	if (!str || *str == '*')
		return ((char *) NULL);
	i = 0;
	while (str[i])
	{
		str = reduce(data, str, i);
		if (!str)
		{
			printf("minishell: no matches found: %s\n", data->sub_str);
			data->inter->last_exit = 1;
			free(data->sub_str);
			return ((char *) NULL);
		}
		i++;
	}
	str_replace(str, "*", "");
	return (str);
}
