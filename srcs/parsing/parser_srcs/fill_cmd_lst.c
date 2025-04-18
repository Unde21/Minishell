/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:51:01 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/18 10:30:43 by samaouch         ###   ########lyon.fr   */
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

static bool	fill_cmd_args(t_token **current, t_cmd *current_cmd)
{
	t_token	*tmp;
	size_t	i;

	tmp = *current;
	*current = tmp;
	i = 0;
	while (*current != NULL && (*current)->type != PIPE)
	{
		if (is_redir_type((*current)->type) == true)
		{
			if (fill_cmd_special_operator(current, current_cmd) == false)
				return (false);
			continue ;
		}
		current_cmd->args[i++].content = ft_strdup((*current)->content);
		if (current_cmd->args[i - 1].content == NULL)
		{
			print_err(ERR_MALLOC);
			return (false);
		}
		*current = (*current)->next;
	}
	if (current_cmd->nb_args != 0)
		current_cmd->args[i].content = NULL;
	return (true);
}

static bool	new_node_cmd(t_cmd **current_cmd)
{
	(*current_cmd)->next = malloc(sizeof(t_cmd));
	if ((*current_cmd)->next == NULL)
	{
		print_err(ERR_MALLOC);
		return (false);
	}
	(*current_cmd) = (*current_cmd)->next;
	(*current_cmd)->nb_args = 0;
	(*current_cmd)->args = NULL;
	(*current_cmd)->redir = NULL;
	(*current_cmd)->next = NULL;
	return (true);
}

bool	get_cmd_args(t_token *current, t_cmd *cmd)
{
	t_cmd	*current_cmd;

	current_cmd = cmd;
	if (current->type == PIPE)
		return (print_err(ERR_PIPE_FIRST));
	while (current != NULL)
	{
		get_cmd_nb_arg(current, current_cmd);
		if (init_cmd_args(current_cmd) == false
			|| fill_cmd_args(&current, current_cmd) == false)
			return (false);
		if (current != NULL && current->type == PIPE)
		{
			current = current->next;
			if (current->type == PIPE)
				return (print_err(ERR_MULTIPLE_PIPE));
			if (current != NULL)
			{
				if (new_node_cmd(&current_cmd) == false)
					return (false);
			}
		}
	}
	return (true);
}
