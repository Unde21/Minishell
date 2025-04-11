/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 08:46:37 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/11 21:27:32 by samaouch         ###   ########lyon.fr   */
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

static bool get_cmd_args(t_token *current, t_cmd *cmd)
{
	size_t	i;
	t_cmd *current_cmd;
	t_token	*tmp;
	
	current_cmd = cmd;
	while (current != NULL)
	{
		tmp = current;
		get_cmd_nb_arg(current, current_cmd);
		if (init_cmd_args(current_cmd) == false)
		return (false);
		current = tmp;
		i = 0;
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
			current_cmd->args[i++] = ft_strdup(current->content);
			current = current->next;
		}
		current_cmd->args[i] = NULL;
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
			current_cmd->next = NULL;
		}
	}
	return (true);
}

static void	parser(t_data *data, t_cmd *cmd)
{
	if (data->token_lst == NULL || data->token_lst->head == NULL)
		return ;
	if (get_cmd_args(data->token_lst->head, cmd) == false)
		return ;
}

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
	parser(data, data->cmd);
	print_lst_cmd(data->cmd);
	// clear_redir(data->redir);
	clear_cmd(data->cmd);
	clear_token(data->token_lst->head);
	free(data->token_lst);
}
