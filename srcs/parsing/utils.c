/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:34:25 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/29 17:03:33 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

// TODO print_lst en debug
#include <stdio.h>
void	print_lst(t_token *token)
{
	if (token == NULL)
		return ;
	ft_printf("\n\033[37;45mPRINT TOKENISER:\033[0m\n\n");
	while (token != NULL)
	{
		ft_printf("\033[35m-------------------------------------------------------------------------\033[0m\n{");
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
		ft_printf("\n\033[35m-------------------------------------------------------------------------\033[0m\n");
		ft_printf("       				|\n      				v\n");
		token = token->next;
	}
	ft_printf("\033[35m-------------------------------------------------------------------------\n\033[33m{NULL}\033[0m");
	ft_printf("\n\033[35m-------------------------------------------------------------------------\033[0m\n");
}


void	print_lst_cmd(t_cmd *cmd)
{
	size_t	i;
	t_redir	*current_redir;
	
	if (cmd == NULL)
		return ;
	printf("\n\n\n\033[31;44mPRINT PARSER:\033[0m\n\n");
	while (cmd != NULL)
	{
		i = 0;
		ft_printf("\033[34m-------------------------------------------------------------------------\033[0m\n");
		while (cmd->args[i].content)
		{
			if (i == 0)
				ft_printf("\033[32m%s\033[0m", cmd->args[i].content);
			else
				ft_printf("\n\033[32m%s\033[0m", cmd->args[i].content);
			if (cmd->args[i].need_expand == true)
				ft_printf("	\033[32m--> need_expend: Yes\033[0m");
			else
				ft_printf("	\033[32m--> need_expend: No\033[0m");
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
		ft_printf("\n\033[34m-------------------------------------------------------------------------\033[0m\n");
		ft_printf("       				|\n      				v\n");
		cmd = cmd->next;
	}
	ft_printf("\033[34m-------------------------------------------------------------------------\033[0m\n\033[32mNULL\033[0m");
	ft_printf("\n\033[34m-------------------------------------------------------------------------\033[0m\n");
}

void	print_lst_cmd_expand(t_cmd *cmd)
{
	size_t	i;
	t_redir	*current_redir;
	
	if (cmd == NULL)
		return ;
	printf("\n\n\n\033[35;43mPRINT PARSER WITH EXPAND:\033[0m\n\n");
	while (cmd != NULL)
	{
		i = 0;
		ft_printf("\033[33m-------------------------------------------------------------------------\033[0m\n");
		while (cmd->args[i].content)
		{
			if (cmd->args[i].content == NULL)
				break ;
			if (i == 0)
				ft_printf("\033[35m%s\033[0m", cmd->args[i].content);
			else
				ft_printf("\n\033[35m%s\033[0m", cmd->args[i].content);
			++i;
		}
		current_redir = cmd->redir;
		while (current_redir != NULL)
		{	
			if (current_redir->type == 4)
				ft_printf("\033[35m		REDIR: REDIR_IN	\033[0m");
			else if (current_redir->type == 5)
				ft_printf("\033[35m		REDIR: REDIR_OUT\033[0m");
			else if (current_redir->type == 6)
				ft_printf("\033[35m		REDIR: HERE_DOC	\033[0m");
			else if (current_redir->type == 7)
				ft_printf("\033[35m		REDIR: APPEND\033[0m");
			ft_printf("		\033[35mFILE: %s\n\033[0m", current_redir->file);
			current_redir = current_redir->next;
		}
		ft_printf("\n\033[33m-------------------------------------------------------------------------\033[0m\n");
		ft_printf("       				|\n      				v\n");
		cmd = cmd->next;
	}
	ft_printf("\033[33m-------------------------------------------------------------------------\033[0m\n\033[35mNULL\033[0m");
	ft_printf("\n\033[33m-------------------------------------------------------------------------\033[0m\n");
}

int	wich_quote(char *input)
{
	size_t	i;

	i = 0;
	while(input[i])
	{
		if (input[i] == (char)ASCII_DBLE_QUOTE)
			return (ASCII_DBLE_QUOTE);
		else if (input[i] == (char)ASCII_SNGL_QUOTE)
			return (ASCII_SNGL_QUOTE);
		++i;
	}
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

void	skip_quote_dollar(char **input, int is_quote, size_t *word_size, int *count_quote)
{
	if (**input == ASCII_DOLLAR)
	{
		++(*word_size);
		++(*input);
	}
	if (is_quote != NO_QUOTE)
	{
		++(*count_quote);
		++(*input);
		++(*word_size);
	}
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	len;
	size_t	j;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		++j;
	}
	join[i + j] = '\0';
	free(s1);
	return (join);
}
