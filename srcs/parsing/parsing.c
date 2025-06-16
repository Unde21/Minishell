#include "builtins.h"
#include "debug.h"
#include "exec.h"
#include "minishell.h"
#include <stdlib.h>

static bool	tokenizer(t_data *data)
{
	if (handle_token(data, data->line_read, data->token_lst,
			data->token) == false)
		return (false);
	if (DEBUG_VALUE == 1 || DEBUG_VALUE == 5)
		print_lst(data->token_lst->head);
	return (true);
}

static bool	manage_expansion(t_data *data, int prev_return_value)
{
	expand_tokens(data->cmd);
	if (DEBUG_VALUE == 2 || DEBUG_VALUE == 5)
		print_lst_cmd(data->cmd);
	if (data->return_value == 0)
		data->return_value = prev_return_value;
	if (handle_expansion(data, data->cmd, true) == false
		|| expand_redir(data, data->cmd) == false)
		return (false);
	if (DEBUG_VALUE == 3 || DEBUG_VALUE == 5)
		print_lst_cmd_expand(data->cmd);
	// if (handle_expansion(data, data->cmd, true) == false
	// 	|| expand_redir(data, data->cmd) == false)
	// 	return (false);
	if (split_wildcards_file(data->cmd) == false
		|| handle_split_expand(data->cmd) == false)
		return (false);
	if (DEBUG_VALUE == 4 || DEBUG_VALUE == 5)
		print_final_lst(data->cmd);
	return (true);
}

bool	parsing(t_data *data)
{
	int	prev_return_value;

	prev_return_value = data->return_value;
	data->return_value = 0;
	if (tokenizer(data) == false)
		return (false);
	if (parser(data, &data->cmd) == false)
		return (false);
	if (manage_expansion(data, prev_return_value) == false)
		return (false);
	return (true);
}
