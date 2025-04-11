/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:10:18 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/11 23:50:28 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	get_input(t_data *data)
{
	char	*str;
	char	*path;

	//TODO Voir ce qu on met ! 
	path = getcwd(NULL, 0);
	str = ft_strjoin(path, "$ ");
	free(path);
	data->line_read = readline(str);
	if (data->line_read != NULL)
		add_history(data->line_read);
	while (data->line_read != NULL)
	{
		ft_printf("\nline : {%s}\n\n", data->line_read);
		parsing(data); //BUG segfault if input == NULL
		free(data->line_read);
		data->line_read = readline(str);
		if (data->line_read != NULL)
			add_history(data->line_read);
	}
	rl_clear_history();
	free(data->line_read);
	free(str);
}
