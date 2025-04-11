/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:51:01 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/12 00:27:56 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	get_cmd_nb_arg(t_token *current, t_cmd *cmd)
{
	cmd->nb_args = 0;
	while (current != NULL && current->type != PIPE)
	{
		if (current->type == REDIR_IN || current->type == REDIR_OUT
				|| current->type == HERE_DOC || current->type == APPEND)
		{
			current = current->next;
			if (current != NULL)
				current = current->next;
			continue ;
		}
		++cmd->nb_args;
		current = current->next;
	}
}

static bool fill_cmd_args(t_token **current, t_cmd *current_cmd)
{
	t_token  *tmp;
	size_t	i;

	tmp = *current;
	get_cmd_nb_arg(*current, current_cmd);
	if (init_cmd_args(current_cmd) == false)
		return (false);
	*current = tmp;
	i = 0;
	while (*current != NULL && (*current)->type != PIPE)
	{
		if ((*current)->type == REDIR_IN || (*current)->type == REDIR_OUT
				|| (*current)->type == HERE_DOC || (*current)->type == APPEND)
		{
			*current = (*current)->next;
			if (current != NULL)
				*current = (*current)->next;
			continue ;
		}
		current_cmd->args[i] = ft_strdup((*current)->content);
		if (current_cmd->args[i] == NULL)
		{
			ft_dprintf(2, ERR_MALLOC);
			return (false);
		}
		++i;
		*current = (*current)->next;
	}
	current_cmd->args[i] = NULL;
	return (true);
}

bool get_cmd_args(t_token *current, t_cmd *cmd)
{
	t_cmd *current_cmd;

	current_cmd = cmd;
	while (current != NULL)
	{
		if (fill_cmd_args(&current, current_cmd) == false)
			return (false);
		if (current != NULL && current->type == PIPE)
		{
			current = current->next;
			current_cmd->next = malloc(sizeof(t_cmd));
			if (current_cmd->next == NULL)
			{
				ft_dprintf(2, ERR_MALLOC);
				return (false);
			}
			current_cmd = current_cmd->next;
			current_cmd->nb_args = 0;
			current_cmd->redir = NULL;
			current_cmd->next = NULL;
		}
	}
	return (true);
}
