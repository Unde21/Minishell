/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:49:38 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/12 00:10:12 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO -> handle free if error... mb change this function to booleen function
void	parser(t_data *data, t_cmd *cmd)
{
	if (data->token_lst == NULL || data->token_lst->head == NULL)
		return ;
	if (get_cmd_args(data->token_lst->head, cmd) == false)
		return ;
	if (add_special_operator_to_cmd(data->token_lst->head, cmd) == false)
		return ;
}

