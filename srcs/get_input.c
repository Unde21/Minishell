/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:10:18 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/02 13:50:07 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

void	get_input(t_data *data)
{
	char	*str;
	char	*path;
	
	path = getcwd(NULL, 0);
	str = ft_strjoin(path, "$ ");
	free(path);
	data->line_read = readline(str);
	if (data->line_read != NULL)
		add_history(data->line_read);
	while(data->line_read != NULL)
	{
		ft_printf("line : %s\n", data->line_read);
		free(data->line_read);
		data->line_read = readline(str);
		if (data->line_read != NULL)
			add_history(data->line_read);
	}
	rl_clear_history();
	free(data->line_read);
	free(str);
}
