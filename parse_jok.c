/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_jok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:28:50 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/29 18:36:10 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

size_t	len_value(t_data *data, char *var)
{
	t_listenv	*tmp;

	tmp = *(data->listenv);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var) == 0)
			return (ft_strlen(tmp->value));
		tmp = tmp->next;
	}
	tmp = *(data->var_tmp);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var) == 0)
			return (ft_strlen(tmp->value));
		tmp = tmp->next;
	}
	return (0);
}

char	*parse_jok(char *str, int i)
{
	char	*tmp;
	int		j;
	char	*var;

	var = (char *) NULL;
	if ((!str[i + 1] && str[i - 1] == ' ')
		|| (str[i - 1] == ' ' && str[i + 1] == ' '))
		return (ft_strdup(&str[i]));
	if (str[i + 1] && str[i + 1] != ' ')
		var = ft_strndup(&str[i], len_variable(&str[i]));
	else if (str[i - 1] && str[i - 1] != ' ')
	{
		tmp = &str[i];
		j = 0;
		while (tmp && *tmp != ' ')
		{
			j++;
			tmp--;
		}
		tmp++;
		var = ft_strndup(tmp, j);
	}
	return (var);
}

char	*reduce_bis(t_data *data, char *str)
{
	t_jok	joker;

	joker.tmp = substr(str);
	data->sub_str = ft_strdup(joker.tmp);
	joker.beg = malloc(ft_strlen(joker.tmp) + 1);
	joker.end = malloc(ft_strlen(joker.tmp) + 1);
	ft_cpy(joker.beg, joker.end, joker.tmp);
	joker.sub = parse_sub(joker.beg);
	free(joker.beg);
	if (!joker.sub)
		return ((char *) NULL);
	joker.sp = ft_split(joker.sub, ' ');
	joker.tmp1 = reduce_m(joker.sp, joker.end);
	if (!joker.tmp1)
		return ((char *) NULL);
	joker.beg = malloc(ft_strlen(str) + ft_strlen(joker.tmp1) + 1);
	ft_strcpy(joker.beg, str);
	str_replace(joker.beg, joker.tmp, joker.tmp1);
	return (joker.beg);
}

int	calcul_flag(char *str, int i, int flag)
{
	if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
		flag++;
	else if (str[i] == '\'' && str[i - 1] != '\\' && flag == 0)
		flag--;
	return (flag);
}

char	*replace_value(t_data *data, char *line)
{
	char	*tmp;
	char	*str;
	int		i;
	int		flag;

	str = line;
	i = -1;
	tmp = (char *) NULL;
	flag = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
			flag = calcul_flag(str, i, flag);
		if (str[i] == '$' && flag == 0)
		{
			str = parse_value(data, str, 0);
			if (tmp)
				free(tmp);
			tmp = str;
		}
	}
	return (str);
}
