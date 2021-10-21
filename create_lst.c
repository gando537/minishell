/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:07:28 by mdiallo           #+#    #+#             */
/*   Updated: 2021/01/02 01:57:43 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	add_cmd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;

	if (!cmd || !new)
		return ;
	if (!(*cmd))
	{
		*cmd = new;
		return ;
	}
	tmp = *cmd;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

t_cmd	*create_cmd(char *cmd)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup(cmd);
	new->next = (struct s_cmd *) NULL;
	return (new);
}

t_cmd	**list_cmd(void)
{
	t_cmd	**new;

	new = malloc(sizeof(t_cmd *));
	if (!new)
		return (NULL);
	*new = NULL;
	return (new);
}

t_listenv	*ft_new_elm(char *name, char *value)
{
	t_listenv	*new_maillon;

	new_maillon = malloc(sizeof(t_listenv));
	if (!new_maillon)
		return (NULL);
	new_maillon->name = ft_strdup(name);
	new_maillon->value = value;
	new_maillon->next = (struct s_listenv *) NULL;
	return (new_maillon);
}

t_listenv	**create_listenv(void)
{
	t_listenv	**new;

	new = malloc(sizeof(t_listenv *));
	if (!new)
		return (NULL);
	*new = NULL;
	return (new);
}
