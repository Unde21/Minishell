/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 08:46:37 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/18 08:50:43 by samaouch         ###   ########lyon.fr   */
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
	if (parser(data, data->cmd) == false)
	{
		clear_cmd(data->cmd);
		clear_token(data->token_lst->head);
		return ;
	}
	// if (expand_tokens(data->cmd) == false)
	// {
	// 	clear_cmd(data->cmd);
	// 	clear_token(data->token_lst->head);
	// 	return ;
	// }
	print_lst_cmd(data->cmd);
	clear_cmd(data->cmd);
	clear_token(data->token_lst->head);
	free(data->token_lst);
}
