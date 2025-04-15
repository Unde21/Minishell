/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 08:46:37 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/15 18:32:16 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	parsing(t_data *data)
{
	if (init_lst(data) == false)
		return ;
	if (handle_token(data->line_read, data->token_lst, data->token) == false)
	{
		clear_token(data->token_lst->head);
		free(data->token_lst);
		return ;
	}
	print_lst(data->token_lst->head);
	parser(data, data->cmd);
	print_lst_cmd(data->cmd);
	clear_cmd(data->cmd);
	clear_token(data->token_lst->head);
	free(data->token_lst);
}
