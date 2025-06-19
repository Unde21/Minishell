#include "parsing.h"
#include <stdlib.h>

static bool	check_error(t_token *current)
{
	t_token	*tmp;

	tmp = current->next;
	while (current->next != NULL)
	{
		if ((is_redir_type(current->type) && is_redir_type(tmp->type))
			|| (is_redir_type(current->type) && tmp->type == PIPE))
			return (false);
		current = current->next;
		tmp = tmp->next;
	}
	return (true);
}

bool	parser(t_data *data, t_cmd **cmd, int prev_return_value)
{
	if (data->token_lst == NULL || data->token_lst->head == NULL)
	{
		data->return_value = prev_return_value;
		return (false);
	}
	if (check_error(data->token_lst->head) == false)
	{
		data->return_value = 1;
		return (print_err_false(ERR_NO_FILE));
	}
	if (get_cmd_args(data->token_lst->head, cmd) == false)
	{
		data->return_value = 1;
		return (false);
	}
	return (true);
}
