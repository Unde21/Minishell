#include "minishell.h"
#include "parsing.h"

size_t	new_node_pipes(t_token **new, t_data *data)
{
	*new = new_token("|", PIPE);
	if (*new == NULL)
		data->return_value = 1;
	return (1);
}

size_t	new_node_redir_out(t_token **new, t_data *data)
{
	*new = new_token(">", REDIR_OUT);
	if (*new == NULL)
		data->return_value = 1;
	return (1);
}

size_t	new_node_redir_in(t_token **new, t_data *data)
{
	*new = new_token("<", REDIR_IN);
	if (*new == NULL)
		data->return_value = 1;
	return (1);
}

size_t	new_node_here_doc(t_token **new, t_data *data)
{
	*new = new_token("<<", HERE_DOC);
	if (*new == NULL)
		data->return_value = 1;
	return (2);
}

size_t	new_node_append(t_token **new, t_data *data)
{
	*new = new_token(">>", APPEND);
	if (*new == NULL)
		data->return_value = 1;
	return (2);
}
