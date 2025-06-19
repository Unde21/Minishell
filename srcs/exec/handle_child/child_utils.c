/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:30:14 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:30:15 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	wait_child(pid_t last_pid, int *return_value)
{
	pid_t	pid;
	int		status;

	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid < 0)
			break ;
		else if (pid == last_pid)
		{
			if (WIFEXITED(status))
				*return_value = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				*return_value = 128 + WTERMSIG(status);
				if (*return_value == 131)
					ft_dprintf(STDOUT_FILENO, QUIT);
			}
		}
	}
}

size_t	get_total_length(char **params)
{
	size_t	len;

	len = 0;
	while (params[len])
		++len;
	return (len);
}
