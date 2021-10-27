/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:57:54 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/27 20:35:50 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	invalid_quote(char *str)
{
	int	i;
	int	dq;
	int	sq;

	i = 0;
	dq = 0;
	sq = 0;
	while (str[i])
	{
		if (str[i] == '"' && (i == 0 || str[i - 1] != '\\')
			&& dq == 0 && sq == 0)
			++dq;
		else if (str[i] == '"' && (i == 0 || str[i - 1] != '\\') && dq == 1)
			--dq;
		if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\')
			&& sq == 0 && dq == 0)
			++sq;
		else if (str[i] == '\'' && (i == 0 || str[i - 1] != '\\') && sq == 1)
			--sq;
		i++;
	}
	return (dq + sq);
}

void	double_quotes_(t_data *data, char *line_read, int i, char *value)
{
	int		j;
	char	*name;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	j = 0;
	value = (char *)malloc(sizeof(char) * ft_strlen(line_read) + 1);
	while (line_read[++i] && (line_read[i] != '"' || line_read[i] == '\\'))
		value[j++] = line_read[i];
	value[j] = '\0';
	name = ft_itoa(getpid() + i);
	tmp = ft_strjoin("$", name);
	free(name);
	add_var(data, data->var_tmp, tmp, value);
	tmp1 = ft_strjoin("\"", value);
	tmp2 = ft_strjoin(tmp1, "\"");
	free(tmp1);
	str_replace(line_read, tmp2, tmp);
	free(tmp2);
	free(tmp);
}

void	simple_quotes_(t_data *data, char *line_read, int i, char *value)
{
	int		j;
	char	*name;
	char	*tmp;
	char	*tmp1;
	char	*tmp2;

	j = 0;
	value = (char *)malloc(sizeof(char) * ft_strlen(line_read) + 1);
	while (line_read[++i] && (line_read[i] != '\'' || line_read[i] == '\\'))
		value[j++] = line_read[i];
	value[j] = '\0';
	name = ft_itoa(getpid() + i);
	tmp = ft_strjoin("$", name);
	free(name);
	add_var(data, data->var_tmp, tmp, value);
	tmp1 = ft_strjoin("\'", value);
	tmp2 = ft_strjoin(tmp1, "\'");
	free(tmp1);
	str_replace(line_read, tmp2, tmp);
	free(tmp2);
	free(tmp);
}

void	quotes_(t_data *data, char *line_read)
{
	int		i;
	char	*value;

	i = 0;
	value = (char *) NULL;
	while (line_read[i])
	{
		if (line_read[i] == '"' && (i == 0 || line_read[i - 1] != '\\'))
			double_quotes_(data, line_read, i, value);
		if (line_read[i] == '\'' && (i == 0 || line_read[i - 1] != '\\'))
			simple_quotes_(data, line_read, i, value);
		if (line_read[i])
			i++;
	}
}
