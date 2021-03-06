/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 11:48:03 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/17 13:20:31 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Includes/minishell.h"

static int	ft_nb_sep(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if ((str[i] == '|' && str[i + 1] == '|') || \
			(str[i] == '&' && str[i + 1] == '&'))
			n++;
		i++;
	}
	return (n);
}

static char	*parsing_cmd(char *r)
{
	int		nb_sep;
	char	*tmp;

	nb_sep = ft_nb_sep(r);
	tmp = r;
	if (nb_sep)
	{
		r = malloc(sizeof(char) * ft_strlen(r) + 2 * nb_sep + 1);
		ft_strcpy(r, tmp);
		replace_andor(r);
		free(tmp);
	}
	return (r);
}

static int	lst_cmd_b(char **tmp, char **sp, int i)
{
	char	*tmp1;

	while (sp[++i] && ft_strcmp(sp[i], "||") && ft_strcmp(sp[i], "&&"))
	{
		tmp1 = ft_strjoin(*tmp, " ");
		free(*tmp);
		*tmp = ft_strjoin(tmp1, sp[i]);
		free(tmp1);
	}
	return (i);
}

t_cmd	**lst_cmd(char *r)
{
	int		i;
	char	**sp;
	char	*tmp;
	char	*temp;
	t_cmd	**cmd;

	i = 0;
	temp = parsing_cmd(r);
	sp = ft_split(temp, ' ');
	free(temp);
	cmd = list_cmd();
	while (sp[i])
	{
		tmp = ft_strdup(sp[i]);
		i = lst_cmd_b(&tmp, sp, i);
		add_cmd(cmd, create_cmd(tmp));
		if (sp[i] && (!ft_strcmp(sp[i], "||") || !ft_strcmp(sp[i], "&&")))
			add_cmd(cmd, create_cmd(sp[i++]));
		free(tmp);
	}
	free_split(sp);
	return (cmd);
}

char	*manager_bis(t_data *data)
{
	char	*r;
	char	*prompt;

	tputs(tgetstr("vi", NULL), 1, ft_putchar);
	prompt = display_prompt();
	data->prompt = prompt;
	write(1, prompt, ft_strlen(prompt));
	tputs(tgetstr("ve", NULL), 1, ft_putchar);
	r = rl_gets(data, prompt);
	return (r);
}
