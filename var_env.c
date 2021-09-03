/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:58:03 by mdiallo           #+#    #+#             */
/*   Updated: 2021/09/02 19:03:24 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_listenv	*ft_new_elm(char *name, char *value)
{
	t_listenv	*new_maillon;

	new_maillon = malloc(sizeof(t_listenv));
	if (!new_maillon)
		return (NULL);
	new_maillon->name = ft_strdup(name);
    new_maillon->value = ft_strdup(value);
	new_maillon->next = NULL;
	return (new_maillon);
}

// t_stack	*create_elem(void)
// {
// 	t_stack	*new;

// 	new = malloc(sizeof(t_stack));
// 	if (!new)
// 		return (NULL);
// 	return (new);
// }

t_listenv	**create_listenv(void)
{
	t_listenv	**new;

	new = malloc(sizeof(t_listenv *));
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

void	add_var(t_listenv **listenv, char *name, char *value)
{
	t_listenv	*tmp;
	t_listenv	*new;
	int			i;

	i = 0;
	if (*listenv != NULL)
	{
		tmp = *listenv;
		while (tmp != NULL)
		{
			if (ft_strcmp(tmp->name, name) == 0)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
				i = 1 ;
			}
			tmp = tmp->next;
		}
	}
	if (i == 0)
	{
		new = ft_new_elm(name, value);
		push_back(listenv, new);
	}
}

// void	gestion_var()

void	pop_var_bis(t_listenv *curr, char *name)
{
	t_listenv	*prev;

	prev = curr;
	curr = curr->next;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->name, name) == 0)
		{
			prev->next = curr->next;
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	pop_var(t_listenv **listenv, char *name)
{
	t_listenv	*curr;

	if (!*listenv)
		return ;
	curr = *listenv;
	if (ft_strcmp(curr->name, name) == 0)
	{
		*listenv = curr->next;
		free(curr);
		return ;
	}
	pop_var_bis(curr, name);
}
