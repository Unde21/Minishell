#include "exec.h"

bool	is_heredoc(t_data *data)
{
	while (data->cmd->redir != NULL)
	{
		if (data->cmd->redir->type == HERE_DOC)
			return (true);
		data->cmd->redir = data->cmd->redir->next;
	}
	return (false);
}
void	exec_init(t_data *data)
{
	init_listed_env(data);
	if (is_heredoc(data))
		heredoc_init(data);
	free_listed_env(data);
}
