/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:40:48 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/21 11:34:01 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	gand(char *s, t_data *data)
{
	char		**split;
	t_listenv	*tmp;

	if (search_char(s, '='))
	{
		split = ft_split(s, '=');
		add_var(data, data->listenv, split[0], split[1]);
		free_split(split);
		return ;
	}
	tmp = *(data->var_tmp);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, s) == 0)
		{
			add_var(data, data->listenv, s, tmp->value);
			pop_var(data->var_tmp, s);
			return ;
		}
		tmp = tmp->next;
	}
}

void	var_val(t_data *data, char *str)
{
	char		**split;

	split = ft_split(str, '=');
	if (len_split(split) == 2)
		add_var(data, data->var_tmp, split[0], split[1]);
}

int	search_vari(t_data *data, char **split)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (split[i])
	{
		if (search_char(split[i], '='))
		{
			var_val(data, split[i]);
			j++;
		}
		i++;
	}
	return (j);
}

int	checker_op(char *op, t_data *data)
{
	if (!ft_strcmp(op, "||") && data->inter->last_exit)
		return (1);
	if (!ft_strcmp(op, "&&") && data->inter->last_exit== 0)
		return (1);
	return (0);
}
