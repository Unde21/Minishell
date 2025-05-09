#include "minishell.h"
#include "parsing.h"

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

bool	parser(t_data *data, t_cmd **cmd)
{
	if (data->token_lst == NULL || data->token_lst->head == NULL)
		return (false);
	if (check_error(data->token_lst->head) == false)
	{
		ft_dprintf(2, ERR_NO_FILE);
		return (false);
	}
	if (get_cmd_args(data->token_lst->head, cmd) == false)
		return (false);
	return (true);
}
