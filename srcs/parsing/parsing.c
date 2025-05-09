
#include "minishell.h"
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
	if (parser(data, data->cmd) == false)
	{
		clear_cmd(data->cmd);
		clear_token(data->token_lst->head);
		return ;
	}
	expand_tokens(data->cmd);
	if (handle_expansion(data, data->cmd) == false)
	{
		clear_cmd(data->cmd);
		clear_token(data->token_lst->head);
		return ;
	}
	exec_init(data);
	clear_cmd(data->cmd);
	clear_token(data->token_lst->head);
	free(data->token_lst);
}
