#include "exec.h"

bool	first_child(t_data *data, int pipe_fd)
{
}
bool	middle_child(t_data *data, int pipe_fd)
{
}
bool	last_child(t_data *data, int pipe_fd)
{
}

bool	child_init(t_data *data, int pipe_fd, int i)
{
	while (data->cmd != NULL)
	{
		if (i == 1)
			return (first_child(data, pipe_fd));
		else if (data->cmd->next != NULL && data->n_cmd > 1)
			return (middle_childs(data, pipe_fd));
		else if (data->cmd->next == NULL && data->n_cmd > 1)
			return (last_child(data, pipe_fd));
		data->cmd = data->cmd->next;
	}
	return (true);
}
