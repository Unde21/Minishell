
#include "minishell.h"

//TODO -> handle free if error... mb change this function to booleen function
bool	parser(t_data *data, t_cmd *cmd)
{
	if (data->token_lst == NULL || data->token_lst->head == NULL)
		return (false);
	if (get_cmd_args(data->token_lst->head, cmd) == false)
		return (false);
	return (true);
}
