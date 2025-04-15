/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:49:38 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/15 18:57:54 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO -> handle free if error... mb change this function to booleen function
bool	parser(t_data *data, t_cmd *cmd)
{
	if (data->token_lst == NULL || data->token_lst->head == NULL)
		return (false);
	if (get_cmd_args(data->token_lst->head, cmd) == false)
		return (false);
	return (true);
}
