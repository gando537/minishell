/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 18:20:19 by mdiallo           #+#    #+#             */
/*   Updated: 2021/08/22 01:14:48 by mdiallo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' \
			|| c == '\f' || c == '\n' || c == '\r');
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	size;
	char	*p_s1;
	char	*p_s2;
	char	*new_str;
	char	*p_new_str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	p_s1 = s1;
	p_s2 = s2;
	p_new_str = new_str;
	while (*p_s1)
		*p_new_str++ = *p_s1++;
	while (*p_s2)
		*p_new_str++ = *p_s2++;
	*p_new_str = '\0';
	return (new_str);
}

// void	ft_execpath(int writefd, char *cmd)
// {
// 	char	**cmd1;
// 	char	*tmp;

// 	tmp = get_path(cmd);
// 	cmd1 = ft_split(tmp, ' ');
// 	dup2(writefd, 1);
// 	close(writefd);
// 	execve(tmp, cmd1, NULL);
// 	write(writefd, "\n", 1);
// }

// char	*ft_path(char *cmd)
// {
// 	int 	wstatus;
// 	int		my_pipe[2];
// 	pid_t	childpid;
// 	char	*path;

// 	if (pipe(my_pipe) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	childpid = fork();
// 	if (childpid == 0)
// 	{
// 		close(my_pipe[0]);
// 		ft_execpath(my_pipe[1], cmd);
// 		exit(0);
// 	}
// 	close(my_pipe[1]);
// 	get_next_line(&path, my_pipe[0]);
// 	close(my_pipe[0]);
// 	waitpid(childpid, &(wstatus), WUNTRACED | WCONTINUED);
// 	return (path);
// }