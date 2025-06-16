#include "builtins.h"
#include "exec.h"

void	free_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->full_line)
			free(tmp->full_line);
		free(tmp);
	}
}

void	close_fd(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pipe_fd[0] != -1)
			close(cmd->pipe_fd[0]);
		if (cmd->pipe_fd[1] != -1)
			close(cmd->pipe_fd[1]);
		cmd = cmd->next;
	}
}
void	clear_exec(t_data *data)
{
	close_fd(data->cmd);
	free_list((t_token *)data->cmd);
	free_list((t_token *)data->listed_env);
}