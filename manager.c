/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:43:47 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/01 17:52:34 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

static char	*manager_bis(t_data *data)
{
	char 	*r;
	char	*prompt;

	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	prompt = display_prompt();
	data->prompt = prompt;
	write(1, prompt, ft_strlen(prompt));
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	r = rl_gets(data, prompt);
	return (r);
}

static void	check_global(char *r)
{
	char	**cmd_split;

	if (!valid_syntax(r))
		exit (1);
	if (search_char(r, '>'))
	{
		str_replace(r, ">>", "");
		str_replace(r, ">", "");
	}
	cmd_split = ft_split(r, ' ');
	if (check_redir(r))
		r = redirection(r);
	if (ft_checker_cmd(r, cmd_split))
		exit (127);
}

static char	*get_manage(t_data *data, char *cmd)
{
	char	**sp;
	char	*line_rd;
	
	line_rd = parse_cmd(data, cmd);
	if (!line_rd)
		return ((char *)NULL);
	sp = ft_split(line_rd, ' ');
	if (*sp)
	{
		if (builti_bis_(data, sp) || checker_builti(line_rd, sp, data))
		{
			data->last_exit = 0;
			return ((char *)NULL);
		}
	}
	free_split(sp);
	return (line_rd);
}

static void	manager_w(t_data *data, char *line)
{
	t_fork	fork_;

	fork_.childpid = fork();
	init_data(data, line);
	if (fork_.childpid == 0)
	{
		check_global(line);
		ft_pipex(data);
	}
	waitpid(fork_.childpid, &(fork_.wstatus), WUNTRACED | WCONTINUED);
	data->last_exit = WEXITSTATUS(fork_.wstatus);
}

void	manager(t_data *data)
{
	char 	*r;
	char	*line;
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
		line = get_manage(data, tmp->cmd);
		if (!line)
		{
			tmp = loop_cmd(data, tmp);;
			continue ;
		}
		fcnt_exit(line, data);
		manager_w(data, line);
		tmp = loop_cmd(data, tmp);
	}
}