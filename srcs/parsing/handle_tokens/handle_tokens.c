#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

t_token	*new_token(char *content, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
	{
		print_err(ERR_MALLOC);
		return (NULL);
	}
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
	while (*input != '\0' && error == false)
	{
		if (*input == '|')
			input += new_node_pipes(&current, &error);
		else if (*input == '>' && *(input + 1) == '>')
			input += new_node_append(&current, &error);
		else if (*input == '>')
			input += new_node_redir_out(&current, &error);
		else if (*input == '<' && *(input + 1) == '<')
			input += new_node_here_doc(&current, &error);
		else if (*input == '<')
			input += new_node_redir_in(&current, &error);
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
