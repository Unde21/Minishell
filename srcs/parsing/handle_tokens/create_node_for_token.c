/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node_for_token.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:34:57 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/11 14:33:14 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	new_node_pipes(t_token **new)
{
	*new = new_token("|", PIPE);
	return (1);
}

size_t	new_node_redir_out(t_token **new)
{
	*new = new_token(">", REDIR_OUT);
	return (1);
}

size_t	new_node_redir_in(t_token **new)
{
	*new = new_token("<", REDIR_IN);
	return (1);
}

size_t	new_node_here_doc(t_token **new)
{
	*new = new_token("<<", HERE_DOC);
	return (2);
}

size_t	new_node_append(t_token **new)
{
	*new = new_token(">>", APPEND);
	return (2);
}
