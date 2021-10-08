/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:12:06 by mdiallo           #+#    #+#             */
/*   Updated: 2021/01/01 01:49:46 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

t_hist	*create_hist(char *cmd)
{
	t_hist	*new;

	new = malloc(sizeof(t_hist));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup(cmd);
	new->next = (struct s_hist *) NULL;
	new->prev = (struct s_hist *) NULL;
	return (new);
}

t_hist	**list_hist(void)
{
	t_hist	**new;

	new = malloc(sizeof(t_hist *));
	if (!new)
		return (NULL);
	*new = NULL;
	return (new);
}

void	add_hist(t_data *data, char *cmd)
{
	t_hist	*new;

	if (*(data->hist) && !ft_strcmp(cmd, (*(data->hist))->cmd))
		return ;
	new = create_hist(cmd);
	if (new == NULL || data->hist == NULL)
		return ;
	if (*(data->hist))
	{
		new->next = *(data->hist);
		(*(data->hist))->prev = new;
	}
	*(data->hist) = new;
	data->hist_curr_up = new;
	data->hist_curr_down = new->prev;
}
