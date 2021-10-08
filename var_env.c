/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 13:58:03 by mdiallo           #+#    #+#             */
/*   Updated: 2021/01/01 02:22:18 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	var_bis(t_listenv *tmp, char *name, char *value)
{
	int	i;

	i = 0;
	if (ft_strcmp(tmp->name, name) == 0)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
		i = 1;
	}
	return (i);
}

char	*parse_value(t_data *data, char *value)
{
	int		j;
	char	*s;
	char	*new_val;
	char	*substr;

	s = (char *) NULL;
	substr = ft_substr(value, '$');
	if (substr)
		s = _var_mp(data, substr + 1);
	new_val = malloc(ft_strlen(value) + ft_strlen(s) + 1);
	j = -1;
	while (value[++j])
		new_val[j] = value[j];
	new_val[j] = '\0';
	if (s)
		str_replace(new_val, substr, s);
	return (new_val);
}

void	add_var(t_data *data, t_listenv **listenv, char *name, char *value)
{
	t_listenv	*tmp;
	t_listenv	*new;
	char		*new_val;
	int			i;

	i = 0;
	new_val = parse_value(data, value);
	if (*listenv != NULL)
	{
		tmp = *listenv;
		while (tmp != NULL)
		{
			i = var_bis(tmp, name, new_val);
			tmp = tmp->next;
		}
	}
	if (i == 0)
	{
		new = ft_new_elm(name, new_val);
		push_back(listenv, new);
	}
	free(new_val);
}

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
