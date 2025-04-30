/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_special_operator_cmd.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 23:01:49 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/30 16:41:47 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	add_new_redir_back(t_cmd *current_cmd, t_redir *new_redir)
{
	t_redir	*last;

	last = NULL;
	if (current_cmd->redir == NULL)
		current_cmd->redir = new_redir;
	else
	{
		last = current_cmd->redir;
		while (last->next)
			last = last->next;
		last->next = new_redir;
	}
}

bool	fill_cmd_special_operator(t_token **current, t_cmd *current_cmd)
{
	t_redir			*new_redir;
	t_token_type	type;

	if (is_redir_type((*current)->type) == true)
	{
		type = (*current)->type;
		*current = (*current)->next;
		if (*current == NULL)
			return (print_err(ERR_NO_FILE));
		new_redir = malloc(sizeof(t_redir));
		if (new_redir == NULL)
			return (print_err(ERR_MALLOC));
		new_redir->type = type;
		new_redir->file = ft_strdup((*current)->content);
		if (new_redir->file == NULL)
		{
			free(new_redir);
			return (print_err(ERR_MALLOC));
		}
		new_redir->next = NULL;
		add_new_redir_back(current_cmd, new_redir);
		*current = (*current)->next;
	}
	return (true);
}
