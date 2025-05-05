#include "minishell.h"
#include "debug.h"
#include <stdlib.h>

void	parsing(t_data *data)
{
	if (init_lst(data) == false)
		return ;
	if (handle_token(data->line_read, data->token_lst, data->token) == false)
	{
		clear_token(data->token_lst->head);
		free(data->token_lst);
		return ;
	}
	if (DEBUG_VALUE == 1 || DEBUG_VALUE == 5)
		print_lst(data->token_lst->head);
	if (parser(data, data->cmd) == false)
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
	clear_cmd(data->cmd);
	clear_token(data->token_lst->head);
	free(data->token_lst);
}
