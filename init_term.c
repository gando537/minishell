/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 15:44:28 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/03 14:37:41 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

int	fctn_ctrl(t_gnl gnl, t_data *data, char **line)
{
	if (gnl.buf[0] == 12)
	{
		clear_sc();
		write(1, data->prompt, ft_strlen(data->prompt));
		write(0, *line, ft_strlen(*line));
		return (1);
	}
	if (gnl.buf[0] == 4)
	{
		free(*line);
		*line = ft_strdup("exit");
		write(1, "\n", 1);
		return (2);
	}
	if (gnl.buf[0] == 3)
	{
		write(1, "\n", 1);
		return (2);
	}
	if (gnl.buf[0] == 9)
		return (3);
	return (0);
}

static char	*init_key(int key)
{
	static char up[] = {27, 91, 65, 0};
	static char right[] = {27, 91, 67, 0};
	static char left[] = {27, 91, 68, 0};
	static char down[] = {27, 91, 66, 0};

	if (key == 0)
		return (up);
	if (key == 1)
		return (right);
	if (key == 2)
		return (left);
	if (key == 3)
		return (down);
	return (NULL);
}

t_trmkey	*init_termcap(void)
{
	t_trmkey	*trm_key;

	trm_key = malloc(sizeof(t_trmkey));
	if (!(trm_key))
		return (NULL);
	if (tgetent(NULL, getenv("TERM")) <= 0)
		write(2, "minishell: Error Loading terminfo\n", 34);
	trm_key->on = tgetstr("ks", NULL);
	if (!(trm_key->on))
		write(2, "minishell: Error\n", 17);
	trm_key->up = init_key(0);
	trm_key->right = init_key(1);
	trm_key->left = init_key(2);
	trm_key->down = init_key(3);
	trm_key->save = tgetstr("sc", NULL);
	trm_key->reset = tgetstr("rc", NULL);
	trm_key->delk = tgetstr("bc", NULL);
	trm_key->del = tgetstr("dc", NULL);
	trm_key->clear = tgetstr("ce", NULL);
	trm_key->mov_csr = tgetstr("CM", NULL);
	return (trm_key);
}

void	init_terminal(t_data *data)
{
	tcgetattr(0, &(data->old_termios));
	tcgetattr(0, &(data->new_termios));
	data->new_termios.c_lflag &= ~(ICANON);
	data->new_termios.c_lflag &= ~(ECHO);
	data->new_termios.c_cc[VMIN] = 1;
	data->new_termios.c_cc[VTIME] = 0;
	data->new_termios.c_cc[VQUIT] = 0;
	data->new_termios.c_cc[VINTR] = 0;
	data->new_termios.c_cc[VEOF] = 0;
	tcsetattr(0, 0, &(data->new_termios));
}

t_data	*get_shell(char **envp)
{
	t_data	*data;

	data = alloc_data();
	data->hist = list_hist();
	init_terminal(data);
	data->termkey = init_termcap();
	data->listenv = init_listenv(envp);
	data->var_tmp = init_listenv((char **)NULL);
	return (data);
}