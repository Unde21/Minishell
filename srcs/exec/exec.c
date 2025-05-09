#include "exec.h"

bool	is_heredoc(t_data *data)
{
	while (data->redir != NULL)
	{
		printf("coucou\n");
		if (data->redir->type == HERE_DOC)
		{
			printf("HERE_DOC\n");
			return (true);
		}
		data->redir = data->redir->next;
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
