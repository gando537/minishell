/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_wp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 12:10:21 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/01 17:52:39 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

void	add_waitpid(t_fork **wp, t_fork *new)
{
	if (new == NULL || wp == NULL)
		return ;
	if (!*wp)
		new->next = NULL;
	else
		new->next = *wp;
	*wp = new;
}

t_fork	*create_wp(pid_t pid)
{
	t_fork	*new;

	new = malloc(sizeof(t_fork));
	if (!new)
		return (NULL);
	new->childpid = pid;
	new->next = NULL;
	return (new);
}

t_fork	**list_wp(void)
{
	t_fork	**new;

	new = malloc(sizeof(t_fork *));
	if (!new)
		return (NULL);
	*new = NULL;
	return (new);
}

void	push_back(t_listenv **listenv, t_listenv *new)
{
	t_listenv   *p_listenv;

	if (!listenv || !new)
		return ;
	if (!(*listenv))
	{
		*listenv = new;
		return ;
	}
	p_listenv = *listenv;
	while (p_listenv->next != NULL)
		p_listenv = p_listenv->next;
	p_listenv->next = new;
}