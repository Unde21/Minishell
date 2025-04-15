/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_special_operator_cmd.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 23:01:49 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/15 16:41:46 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>


bool fill_cmd_special_operator(t_token **current, t_cmd *current_cmd)
{
	t_redir	*new_redir;
	t_redir	*last;
	t_token_type type;

	if ((*current)->type == REDIR_IN || (*current)->type == REDIR_OUT
		|| (*current)->type == APPEND || (*current)->type == HERE_DOC)
	{
		type = (*current)->type;
		*current = (*current)->next;
		if (*current == NULL)
		{
			ft_dprintf(2, ERR_NO_FILE);
			return (false);
		}
		new_redir = malloc(sizeof(t_redir));
		if (new_redir == NULL)
		{
			ft_dprintf(2, ERR_MALLOC);
			return (false);
		}
		new_redir->type = type;
		new_redir->file = ft_strdup((*current)->content);
		if (new_redir->file == NULL)
		{
			free(new_redir);
			ft_dprintf(2, ERR_MALLOC);
			return (false);
		}
		new_redir->next = NULL;
		if (current_cmd->redir == NULL)
			current_cmd->redir = new_redir;
		else
		{
			last = current_cmd->redir;
			while (last->next)
				last = last->next;
			last->next = new_redir;
		}
		*current = (*current)->next;
	}
	return (true);
}

// static bool fill_cmd_special_operator(t_token **current, t_cmd *current_cmd)
// {
// 	t_redir	*new_redir;
// 	t_redir	*last;
// 	t_token_type type;

// 	while (*current != NULL && (*current)->type != PIPE)
// 	{
// 		if ((*current)->type == REDIR_IN || (*current)->type == REDIR_OUT
// 			|| (*current)->type == APPEND || (*current)->type == HERE_DOC)
// 		{
// 			type = (*current)->type;
// 			*current = (*current)->next;
// 			if (*current == NULL)
// 			{
// 				ft_dprintf(2, ERR_NO_FILE);
// 				return (false);
// 			}
// 			new_redir = malloc(sizeof(t_redir));
// 			if (new_redir == NULL)
// 			{
// 				ft_dprintf(2, ERR_MALLOC);
// 				return (false);
// 			}
// 			new_redir->type = type;
// 			new_redir->file = ft_strdup((*current)->content);
// 			if (new_redir->file == NULL)
// 			{
// 				free(new_redir);
// 				ft_dprintf(2, ERR_MALLOC);
// 				return (false);
// 			}
// 			new_redir->next = NULL;
// 			if (current_cmd->redir == NULL)
// 				current_cmd->redir = new_redir;
// 			else
// 			{
// 				last = current_cmd->redir;
// 				while (last->next)
// 					last = last->next;
// 				last->next = new_redir;
// 			}
// 		}
// 		*current = (*current)->next;
// 	}
// 	return (true);
// }

// bool add_special_operator_to_cmd(t_token *current, t_cmd *cmd)
// {
// 	t_cmd *current_cmd;

// 	current_cmd = cmd;
// 	while (current != NULL)
// 	{
// 		if (fill_cmd_special_operator(&current, current_cmd) == false)
// 			return (false);
// 		if (current != NULL && current->type == PIPE)
// 		{
// 			current = current->next;
// 			current_cmd = current_cmd->next;
// 		}
// 	}
// 	return (true);
// }
