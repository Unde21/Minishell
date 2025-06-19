#include "parsing.h"
#include <stdlib.h>

t_token	*new_token(char *content, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL)
	{
		print_err_null(ERR_MALLOC);
		return (NULL);
	}
	token->content =ft_strdup(content);
	if (token->content == NULL)
	{
		free(token);
		return (NULL);
	}
	token->type = type;
	token->next = NULL;
	token->in_list = false;
	return (token);
}

static void	save_head_and_tail_lst(t_data *data, t_token_lst *tokens,
		t_token *new)
{
	if (data->return_value != 0)
		return ;
	if (new != NULL &&new->in_list == false)
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

static size_t	skip_isspace(t_data *data, char *input)
{
	size_t	i;

	i = 0;
	data->had_space_before = false;
	while (ft_isspace(*input) == true && *input != '\0')
	{
		++input;
		++i;
		data->had_space_before = true;
	}
	if (data->last_type != WORD)
		data->had_space_before = true;
	return (i);
}

bool	handle_token(t_data *data, char *input, t_token_lst *tokens,
		t_token *current)
{
	size_t	word_size;

	word_size = 0;
	while (*input != '\0' && data->return_value == 0)
	{
		input += skip_isspace(data, input);
		if (*input == '\0')
			break ;
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
			input += handle_word(input, &current, data, word_size);
		save_head_and_tail_lst(data, tokens, current);
	}
	if (data->return_value != 0)
		return (false);
	return (true);
}
