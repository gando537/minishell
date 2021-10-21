/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 13:43:30 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/21 11:50:26 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

t_cmd	*loop_cmd(t_data *data, t_cmd *tmp)
{
	tmp = tmp->next;
	if (tmp && (!ft_strcmp(tmp->cmd, "||") || !ft_strcmp(tmp->cmd, "&&")))
	{
		if (checker_op(tmp->cmd, data))
			tmp = tmp->next;
		else
		{
			while (tmp && !checker_op(tmp->cmd, data))
				tmp = tmp->next;
			if (tmp)
				tmp = tmp->next;
		}
	}
	return (tmp);
}

void	free_data(t_data *data)
{
	free_lst(data->listenv);
	free_lst(data->var_tmp);
	free(data->inter);
	free_hist(data->hist);
	free(data);
}

void	printer_env(t_listenv **listenv)
{
	t_listenv	*tmp;

	if (!*listenv)
		return ;
	tmp = *listenv;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

t_listenv	**init_listenv(char **envp)
{
	int			i;
	char		**sp;
	t_listenv	*new;
	t_listenv	**listenv;

	listenv = create_listenv();
	if (!envp)
		return (listenv);
	i = -1;
	while (envp[++i])
	{
		sp = ft_split(envp[i], '=');
		new = ft_new_elm(sp[0], ft_strdup(sp[1]));
		push_back(listenv, new);
		free_split(sp);
	}
	return (listenv);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	chdir(getenv("HOME"));
	data = get_shell(envp);
	clear_sc();
	while (1)
		manager(data);
	free_data(data);
	tcsetattr(0, TCSANOW, &data->old_termios);
	return (0);
}
