#include "minishell.h"
#include "parsing.h"

size_t	new_node_pipes(t_token **new)
{
	*new = new_token("|", PIPE);
	return (1);
}

size_t	new_node_redir_out(t_token **new)
{
	*new = new_token(">", REDIR_OUT);
	return (1);
}

size_t	new_node_redir_in(t_token **new)
{
	*new = new_token("<", REDIR_IN);
	return (1);
}

size_t	new_node_here_doc(t_token **new)
{
	*new = new_token("<<", HERE_DOC);
	return (2);
}

size_t	new_node_append(t_token **new)
{
	*new = new_token(">>", APPEND);
	return (2);
}
