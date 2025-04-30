/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:19:52 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/30 16:33:12 by samaouch         ###   ########lyon.fr   */
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

bool	handle_token(char *input, t_token_lst *tokens, t_token *current)
{
	bool	error;

	error = false;
	while (*input != '\0')
	{
		if (*input == '|')
			input += new_node_pipes(&current);
		else if (*input == '>' && *(input + 1) == '>')
			input += new_node_append(&current);
		else if (*input == '>')
			input += new_node_redir_out(&current);
		else if (*input == '<' && *(input + 1) == '<')
			input += new_node_here_doc(&current);
		else if (*input == '<')
			input += new_node_redir_in(&current);
		else
			input += handle_word(input, &current, &error);
		if (error != true)
			save_head_and_tail_lst(tokens, current);
		while (ft_isspace(*input) == true)
			++input;
	}
	if (error == true)
		return (false);
	return (true);
}
