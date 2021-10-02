/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_red.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 19:44:21 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/01 17:55:13 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	redir_in(char **tmp, char **tmp2, char **cmd_split, char *r)
{
	if (len_split(tmp2) > 1)
	{
		if (check_file_exist(tmp2[1]) == 0)
		{
			free(r);
			free_split(tmp2);
			free_split(tmp);
			free_split(cmd_split);
			perror("minishell");
			return (1);
		}
	}
	return (0);
}

int	bis(char **tmp, char **tmp2, int i)
{
	free_split(tmp2);
	if (i >= len_split(tmp))
		return (1);
	return (0);
}

int checker_red(char **tmp, char **tmp2, char **cmd_split)
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
		return (1);
	}
	free(p);
	free_split(tmp2);
	return (0);
}

int	checker_cmd_bis(char **tmp, char **cmd_split, int i, char *r)
{
	char	**tmp2;

	tmp2 = ft_split(tmp[i], ' ');
	if (ft_strcmp(tmp2[0], "<") == 0 || ft_strcmp(tmp2[0], "<<") == 0)
	{
		i += 2;
		if (redir_in(tmp, tmp2, cmd_split, r))
			return (1);
		if (bis(tmp, tmp2, i))
			return (2);
		return (0);
	}
	if (checker_red(tmp, tmp2, cmd_split))
		return (1);
	return (4);
}

int	ft_checker_cmd(char *r, char **cmd_split)
{
	char	**tmp;
	int		i;

	if (!r || *r == '\n')
		return (0);
	i = 0;
	tmp = ft_split(r, '|');
	while (tmp[i])
	{
		if (checker_cmd_bis(tmp, cmd_split, i, r) ==  1)
			return (1);
		if (checker_cmd_bis(tmp, cmd_split, i, r) ==  2)
			break ;
		if (checker_cmd_bis(tmp, cmd_split, i, r) ==  0)
			continue ;
		i++;
	}
	free_split(tmp);
	return (0);
}
