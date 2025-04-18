/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:24:52 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/18 09:12:14 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	clear_args(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (i < cmd->nb_args)
	{
		free(cmd->args[i].content);
		++i;
	}
	free(cmd->args);
}
void	clear_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd != NULL)
	{
		tmp = cmd->next;
		if (cmd->redir != NULL)
		{
			free(cmd->redir->file);
			free(cmd->redir);
		}
		clear_args(cmd);
		free(cmd);
		cmd = tmp;
	}
	cmd = NULL;
}

void	clear_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir != NULL)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
	redir = NULL;
}

void	clear_token(t_token *lst)
{
	t_token	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
	lst = NULL;
}

void	free_all(char **str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		++i;
	}
	free(str);
}
