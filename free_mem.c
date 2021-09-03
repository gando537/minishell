/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 16:59:30 by mdiallo           #+#    #+#             */
/*   Updated: 2021/09/01 22:36:29 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_split(char **split)
{
	int	i;
	int	j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
			j++;
		i++;
	}
	return (i);
}

void	free_split(char **split)
{
	int	len;
	int	i;

	if (!*split || !split)
		return ;
	i = 0;
	len = len_split(split);
	while (i < len)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_strdel(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = NULL;
	}
}

void	free_lst(t_listenv **lst)
{
	t_listenv	*tmp;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		ft_strdel(&tmp->name);
		ft_strdel(&tmp->value);
		tmp = tmp->next;
	}

	free(lst);
}

void	all_free(t_data *data, int *my_pipes)
{
	free(my_pipes);
	data->in = 0;
	data->nb_pipes = 0;
	data->o_fd = 1;
	data->i_fd = 0;
	data->j = 0;
}

void	fcnt_exit(char *r, char **cmd_split, 
		struct termios old_termios, t_data *data)
{
	if (ft_strcmp(r, "exit") == 0)
	{
		free(r);
		tcsetattr(0,TCSANOW,&old_termios);
		free_split(cmd_split);
		free_data(data);
		exit(0);
	}
}

t_bool	redir_in(char **tmp, char **tmp2, char **cmd_split)
{
	if (len_split(tmp2) > 1)
	{
		if (check_file_exist(tmp2[1]) == 0)
		{
			free_split(tmp2);
			free_split(tmp);
			free_split(cmd_split);
			perror("minishell");
			return (true);
		}
	}
	return (false);
}

t_bool	bis(char **tmp, char **tmp2, int i)
{
	free_split(tmp2);
	if (i >= len_split(tmp))
		return (true);
	return (false);
}

t_bool checker_red(char **tmp, char **tmp2, char **cmd_split)
{
	char	*p;

	p = get_path(tmp2[0]);
	if (p == NULL)
	{
		printf("minishell: command not found: %s\n", cmd_split[0]);
		free(p);
		free_split(tmp);
		free_split(tmp2);
		free_split(cmd_split);
		return (true);
	}
	free(p);
	free_split(tmp2);
	return (false);
}

t_bool	ft_checker_cmd(char *r, char **cmd_split, 
		struct termios old_termios, t_data *data)
{
	char	**tmp;
	char	**tmp2;
	int		i;
	int		len;

	fcnt_exit(r, cmd_split, old_termios, data);
	i = 0;
	tmp = ft_split(r, '|');
	len = len_split(tmp);
	while (tmp[i])
	{
		tmp2 = ft_split(tmp[i], ' ');
		if (ft_strcmp(tmp2[0], "<") == 0)
		{
			i += 2;
			if (redir_in(tmp, tmp2, cmd_split))
				return (true);
			if (bis(tmp, tmp2, i))
				break;
			continue;
		}
		if (checker_red(tmp, tmp2, cmd_split))
			return (true);
		i++;
	}
	free_split(tmp);
	return (false);
}
