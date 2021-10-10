/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 12:04:19 by mdiallo           #+#    #+#             */
/*   Updated: 2021/10/09 16:03:30 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	check_pip(char **cmd)
{
	int	i;
	int	nb_pip;

	nb_pip = 0;
	if (len_split(cmd) <= 1)
		return (nb_pip);
	i = 1;
	while (cmd[i])
		if (ft_strcmp(cmd[i++], "|") == 0)
			nb_pip++;
	return (nb_pip);
}

int	*creat_pipe(int nb_pipes)
{
	int	i;
	int	*_pipes;

	_pipes = (int *)malloc(sizeof(int) * 2 * nb_pipes);
	if (!_pipes)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < nb_pipes)
	{
		if (pipe(_pipes + i * 2) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (_pipes);
}

static long int	ft_abs(long int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

static int	ft_len(long int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len = 1;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		sign;
	char	*c;

	sign = 1;
	if (n < 0)
		sign = -1;
	len = ft_len(n);
	c = (char *)malloc(sizeof(char) * len + 1);
	if (c == NULL)
		return (0);
	c[len] = '\0';
	len--;
	while (len >= 0)
	{
		c[len] = '0' + ft_abs(n % 10);
		n = ft_abs(n / 10);
		len--;
	}
	if (sign == -1)
		c[0] = '-';
	return (c);
}
