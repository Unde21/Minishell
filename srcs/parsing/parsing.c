#include "builtins.h"
#include "debug.h"
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

bool	parsing(t_data *data)
{
	if (tokenizer(data) == false)
		return (false);
	if (parser(data, &data->cmd) == false)
		return (false);
	expand_tokens(data->cmd);
	if (DEBUG_VALUE == 2 || DEBUG_VALUE == 5)
		print_lst_cmd(data->cmd);
	if (handle_expansion(data, data->cmd) == false)
		return (false);
	if (DEBUG_VALUE == 3 || DEBUG_VALUE == 5)
		print_lst_cmd_expand(data->cmd);
	if (ft_strcmp(data->cmd->args->content, "exit") == 0)
	{
		ft_exit(data, data->cmd->args);
	}
	return (true);
}
