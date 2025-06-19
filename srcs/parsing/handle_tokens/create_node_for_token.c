/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_for_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:33:49 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:33:50 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

size_t	new_node_pipes(t_token **new, t_data *data)
{
	*new = new_token("|", PIPE);
	if (*new == NULL)
		data->return_value = 1;
	data->last_type = PIPE;
	return (1);
}

size_t	new_node_redir_out(t_token **new, t_data *data)
{
	*new = new_token(">", REDIR_OUT);
	if (*new == NULL)
		data->return_value = 1;
	data->last_type = REDIR_OUT;
	return (1);
}

size_t	new_node_redir_in(t_token **new, t_data *data)
{
	*new = new_token("<", REDIR_IN);
	if (*new == NULL)
		data->return_value = 1;
	data->last_type = REDIR_IN;
	return (1);
}

size_t	new_node_here_doc(t_token **new, t_data *data)
{
	*new = new_token("<<", HERE_DOC);
	if (*new == NULL)
		data->return_value = 1;
	data->last_type = HERE_DOC;
	return (2);
}

size_t	new_node_append(t_token **new, t_data *data)
{
	*new = new_token(">>", APPEND);
	if (*new == NULL)
		data->return_value = 1;
	data->last_type = APPEND;
	return (2);
}
