/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_for_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:34:57 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/03 12:42:38 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t handle_pipes(t_token **new)
{
	*new = new_token("|", PIPE);
	return (1);
}

size_t	handle_redir_out(t_token **new)
{
	*new = new_token(">", REDIR_OUT);
	return (1);
}

size_t	handle_redir_in(t_token **new)
{
	*new = new_token("<", REDIR_IN);
	return (1);
}
