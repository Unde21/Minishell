#include "debug.h"
#include "exec.h"
#include "minishell.h"
#include <stdlib.h>

static bool	tokenizer(t_data *data)
{
	if (handle_token(data->line_read, data->token_lst, data->token) == false)
	{
		clear_cmd(data->cmd);
		clear_token(data->token_lst->head);
		free(data->token_lst);
		return (false);
	}
	if (DEBUG_VALUE == 1 || DEBUG_VALUE == 5)
		print_lst(data->token_lst->head);
	return (true);
}

void	parsing(t_data *data)
{
	if (init_lst(data) == false || tokenizer(data) == false)
		return ;
	if (parser(data, &data->cmd) == false)
	{
		clear_cmd(data->cmd);
		clear_token(data->token_lst->head);
		return ;
	}
	expand_tokens(data->cmd);
	if (DEBUG_VALUE == 2 || DEBUG_VALUE == 5)
		print_lst_cmd(data->cmd);
	if (handle_expansion(data, data->cmd) == false)
	{
		clear_cmd(data->cmd);
		clear_token(data->token_lst->head);
		return ;
	}
	if (DEBUG_VALUE == 3 || DEBUG_VALUE == 5)
		print_lst_cmd_expand(data->cmd);
	data->nb_cmd = get_list_size(data);
	exec_init(data);
	clear_cmd(data->cmd);
	clear_token(data->token_lst->head);
	free(data->token_lst);
}
