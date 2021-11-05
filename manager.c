/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:43:47 by mdiallo           #+#    #+#             */
/*   Updated: 2021/11/05 19:59:14 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

static char	*check_global(char *r, t_data *data)
{
	char	**cmd_split;
	char	**s;
	int		i;

	if (!valid_syntax(r))
		exit (1);
	s = ft_split(r, ' ');
	i = 0;
	while (s[i])
	{
		if (check_redir(s[i]) && s[i + 1])
		{
			r = pop_redir(data, s, r, i);
			break ;
		}
		++i;
	}
	free_split(s);
	cmd_split = ft_split(r, ' ');
	if (data->inter->b != 2)
		if (ft_checker_cmd(r, cmd_split))
			exit (127);
	return (r);
}

void	builti_w(t_data *data, char *cmd)
{
	char	**sp;

	sp = ft_split(cmd, ' ');
	if (*sp)
		builti_bis_(data, sp);
	free_split(sp);
}

int	child(t_data *data, char *line, char *tmp)
{
	char	*l;

	l = (char *) NULL;
	line = check_global(line, data);
	l = parse_cmd(data, line);
	if (!l)
		return (1);
	data->pip = ft_split(l, '|');
	free_var(tmp, l);
	ft_pipex(data);
	return (0);
}

static void	manager_w(t_data *data, char *line)
{
	t_fork	fork_;
	char	*tmp;

	fork_.childpid = fork();
	tmp = (char *) NULL;
	if (check_redir(line) || ft_strstr(line, "|"))
	{
		line = redirection(line);
		tmp = line;
	}
	init_data(data, line);
	builti_w(data, line);
	if (fork_.childpid == 0)
		if (child(data, line, tmp))
			exit(1);
	waitpid(fork_.childpid, &(fork_.wstatus), WUNTRACED | WCONTINUED);
	data->inter->last_exit = WEXITSTATUS(fork_.wstatus);
}

void	manager(t_data *data)
{
	char	*r;
	t_cmd	**cmd;
	t_cmd	*tmp;

	r = manager_bis(data);
	if (!r)
		return ;
	fcnt_exit(r, data);
	cmd = lst_cmd(r);
	tmp = *cmd;
	while (tmp)
	{
		fcnt_exit(tmp->cmd, data);
		manager_w(data, tmp->cmd);
		tmp = loop_cmd(data, tmp);
	}
	free_lst_cmd(cmd);
}
