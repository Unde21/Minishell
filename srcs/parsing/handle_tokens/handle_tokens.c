/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:19:52 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/08 17:42:20 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_token	*new_token(char *content, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->content = ft_strdup(content);
	token->type = type;
	token->next = NULL;
	return (token);
}

static void	save_head_and_tail_lst(t_token_lst *tokens, t_token *new)
{
	if (new != NULL)
	{
		if (tokens->head == NULL)
			tokens->head = new;
		else
			tokens->tail->next = new;
		tokens->tail = new;
		new = NULL;
	}
}

t_token_lst	*handle_token(char *input, t_token_lst *tokens, t_token *current)
{
	while (*input != '\0')
	{
		if (*input == '|')
			input += handle_pipes(&current);
		else if (*input == '>' && *(input + 1) == '>')
			input += handle_append_redir_out(&current);
		else if (*input == '>')
			input += handle_redir_out(&current);
		else if (*input == '<' && *(input + 1) == '<')
			input += handle_append_redir_in(&current);
		else if (*input == '<')
			input += handle_redir_in(&current);
		else
			input += handle_word(input, &current);
		save_head_and_tail_lst(tokens, current);
		while (*input == ' ')
			++input;
	}
	return (tokens);
}
