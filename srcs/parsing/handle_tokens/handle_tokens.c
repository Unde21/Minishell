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
	if (new != NULL && new->in_list == false)
	{
		if (tokens->head == NULL)
			tokens->head = new;
		else
			tokens->tail->next = new;
		tokens->tail = new;
		new->next = NULL;
		new->in_list = true;
	}
}

bool	handle_token(t_data *data, char *input, t_token_lst *tokens,
		t_token *current)
{
	while (*input != '\0' && data->return_value == 0)
	{
		if (*input == '|')
			input += new_node_pipes(&current, data);
		else if (*input == '>' && *(input + 1) == '>')
			input += new_node_append(&current, data);
		else if (*input == '>')
			input += new_node_redir_out(&current, data);
		else if (*input == '<' && *(input + 1) == '<')
			input += new_node_here_doc(&current, data);
		else if (*input == '<')
			input += new_node_redir_in(&current, data);
		else
			input += handle_word(input, &current, data);
		if (data->return_value == 0)
			save_head_and_tail_lst(tokens, current);
		data->had_space_before = false;
		while (ft_isspace(*input) == true)
		{
			++input;
			data->had_space_before = true;
		}
	}
	if (data->return_value != 0)
		return (false);
	return (true);
}
