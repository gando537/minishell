/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 20:27:03 by mdiallo           #+#    #+#             */
/*   Updated: 2021/01/01 02:34:49 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

char	*parse_cmd(t_data *data, char *cmd)
{
	char	*rd;
	char	**sp;

	rd = cmd;
	sp = ft_split(cmd, ' ');
	if (len_split(sp) > 1)
		rd = gestion_var(data, sp);
	if (rd)
		rd = joker_quotes(data, rd);
	free_split(sp);
	if (rd)
		return (rd);
	return ((char *) NULL);
}

char	*rl_gets(t_data *data, char *prompt)
{
	char	*line_read;
	char	*hist;

	line_read = (char *) NULL;
	gnl_term(&line_read, 0, data);
	if (prompt)
		free(prompt);
	hist = stripwhite(line_read);
	if (hist && *hist)
		add_hist(data, hist);
	if (!ft_strcmp(line_read, "clear"))
		return (clear_sc());
	return (line_read);
}

int	ft_chdir(char *r)
{
	char	*p_r;

	if (ft_strlen(r) < 3)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	else
	{
		p_r = &r[3];
		return (checker_path(p_r));
	}
}

int	builtin_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
	{
		printf("minishell: pwd: %s\n", strerror(errno));
		return (1);
	}
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	return (0);
}

int	check_echo(t_data *data, char **cmd_split)
{
	if (len_split(cmd_split) == 1)
	{
		write(data->o_fd, "\n", 1);
		return (1);
	}
	if (len_split(cmd_split) == 2 && ft_strcmp(cmd_split[1], "-n") == 0)
		return (1);
	if (len_split(cmd_split) == 2 && ft_strcmp(cmd_split[1], "$") == 0)
	{
		write(data->o_fd, "\n", 1);
		return (1);
	}
	return (0);
}
