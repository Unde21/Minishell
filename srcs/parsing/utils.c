/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:34:25 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/18 09:04:23 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO delete print_lst
#include <stdio.h>
void	print_lst(t_token *token)
{
	if (token == NULL)
		return ;
	ft_printf("\n\033[37;45mPRINT TOKENISER:\033[0m\n\n");
	while (token->next)
	{
		ft_printf("\033[35m--------------------------------------------------------------------\033[0m\n{");
		if (token->type == 0)
			ft_printf("\033[33m%s}		type: WORD\033[0m", token->content);
		else if (token->type == 1)
			ft_printf("\033[33m%s}		type: SNGL_QUOTE\033[0m", token->content);
		else if (token->type == 2)
			ft_printf("\033[33m%s}		type: DBLE_QUOTE\033[0m", token->content);
		else if (token->type == 3)
			ft_printf("\033[33m%s}		type: PIPE\033[0m", token->content);
		else if (token->type == 4)
			ft_printf("\033[33m%s}		type: REDIR_IN\033[0m", token->content);
		else if (token->type == 5)
			ft_printf("\033[33m%s}		type: REDIR_OUT\033[0m", token->content);
		else if (token->type == 6)
			ft_printf("\033[33m%s}		type: HERE_DOC\033[0m", token->content);
		else if (token->type == 7)
			ft_printf("\033[33m%s}		type: APPEND\033[0m", token->content);
		ft_printf("\n\033[35m--------------------------------------------------------------------\033[0m\n");
		ft_printf("       				|\n      				v\n");
		token = token->next;
	}
	ft_printf("\033[35m--------------------------------------------------------------------\033[0m\n{");
	if (token->type == 0)
		ft_printf("\033[33m%s}		type: WORD\033[0m", token->content);
	else if (token->type == 1)
		ft_printf("\033[33m%s}		type: SNGL_QUOTE\033[0m", token->content);
	else if (token->type == 2)
		ft_printf("\033[33m%s}		type: DBLE_QUOTE\033[0m", token->content);
	else if (token->type == 3)
		ft_printf("\033[33m%s}		type: PIPE\033[0m", token->content);
	else if (token->type == 4)
		ft_printf("\033[33m%s}		type: REDIR_IN\033[0m", token->content);
	else if (token->type == 5)
		ft_printf("\033[33m%s}		type: REDIR_OUT\033[0m", token->content);
	else if (token->type == 6)
		ft_printf("\033[33m%s}		type: HERE_DOC\033[0m", token->content);
	else if (token->type == 7)
		ft_printf("\033[33m%s}		type: APPEND\033[0m", token->content);
	ft_printf("\n\033[35m--------------------------------------------------------------------\033[0m\n");
	ft_printf("       				|\n       				v\n");
	ft_printf("\033[35m--------------------------------------------------------------------\n\033[33m{NULL}\033[0m");
	ft_printf("\n\033[35m--------------------------------------------------------------------\033[0m\n");
}


void	print_lst_cmd(t_cmd *cmd)
{
	size_t	i;
	t_redir	*current_redir;
	
	if (cmd == NULL)
		return ;
	printf("\n\n\n\033[31;44mPRINT PARSER:\033[0m\n\n");
	while (cmd->next != NULL)
	{
		i = 0;
		ft_printf("\033[34m--------------------------------------------------------------------\033[0m\n");
		if (cmd->args != NULL)
		{
			while (cmd->args[i].content)
			{
				if (i == 0)
					ft_printf("\033[32m%s\033[0m", cmd->args[i].content);
				else
					ft_printf("\n\033[32m%s\033[0m", cmd->args[i].content);
				++i;
			}
			current_redir = cmd->redir;
			while (current_redir != NULL)
			{	
				if (current_redir->type == 4)
					ft_printf("\033[32m		REDIR: REDIR_IN	\033[0m");
				else if (current_redir->type == 5)
					ft_printf("\033[32m		REDIR: REDIR_OUT\033[0m");
				else if (current_redir->type == 6)
					ft_printf("\033[32m		REDIR: HERE_DOC	\033[0m");
				else if (current_redir->type == 7)
					ft_printf("\033[32m		REDIR: APPEND\033[0m");
				ft_printf("		\033[32mFILE: %s\n\033[0m", current_redir->file);
				current_redir = current_redir->next;
			}
		}
		ft_printf("\n\033[34m--------------------------------------------------------------------\033[0m\n");
		ft_printf("       				|\n      				v\n");
		cmd = cmd->next;
	}
	ft_printf("\033[34m--------------------------------------------------------------------\033[0m\n");
	i = 0;
	if (cmd->args != NULL)
	{
		while (cmd->args[i].content)
		{
			if (i == 0)
			ft_printf("\033[32m%s\033[0m", cmd->args[i].content);
			else
			ft_printf("\n\033[32m%s\033[0m", cmd->args[i].content);
			++i;
		}
		current_redir = cmd->redir;
		while (current_redir != NULL)
		{
			if (current_redir->type == 4)
				ft_printf("\033[32m		REDIR: REDIR_IN	\033[0m");
			else if (current_redir->type == 5)
				ft_printf("\033[32m		REDIR: REDIR_OUT\033[0m");
			else if (current_redir->type == 6)
				ft_printf("\033[32m		REDIR: HERE_DOC	\033[0m");
			else if (current_redir->type == 7)
				ft_printf("\033[32m		REDIR: APPEND\033[0m");
			ft_printf("	\033[32mFILE: %s\n\033[0m", current_redir->file);
			current_redir = current_redir->next;
		}
	}
	ft_printf("\n\033[34m--------------------------------------------------------------------\033[0m\n");
	ft_printf("       				|\n       				v\n");
	ft_printf("\033[34m--------------------------------------------------------------------\033[0m\n\033[32mNULL\033[0m");
	ft_printf("\n\033[34m--------------------------------------------------------------------\033[0m\n");
}

int	wich_quote(int c)
{
	if (c == ASCII_DBLE_QUOTE)
		return (ASCII_DBLE_QUOTE);
	else if (c == ASCII_SNGL_QUOTE)
		return (ASCII_SNGL_QUOTE);
	return (0);
}

bool	is_redir_type(t_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT
		|| type == HERE_DOC || type == APPEND)
		return (true);
	return (false);
}

bool	print_err(char *str_error)
{
	ft_dprintf(2, "%s", str_error);
	return (false);
}
