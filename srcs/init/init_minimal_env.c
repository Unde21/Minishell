/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimal_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:31:02 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:31:03 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "parsing.h"
#include <stdlib.h>

bool	minimal_env(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		pwd = ft_strdup("/");
		if (pwd == NULL)
		{
			data->return_value = 1;
			return (print_err_false(ERR_MALLOC));
		}
	}
	if (create_first_node(data, pwd) == false)
		return (false);
	if (fill_next_node_minimal(data) == false)
	{
		data->return_value = 1;
		return (false);
	}
	return (true);
}
