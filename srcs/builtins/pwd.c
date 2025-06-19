/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:29:56 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:29:57 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

bool	ft_pwd(t_data *data)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		ft_dprintf(2, ERR_PWD);
		data->return_value = 1;
		return (true);
	}
	ft_dprintf(STDOUT_FILENO, "%s\n", path);
	free(path);
	return (true);
}
