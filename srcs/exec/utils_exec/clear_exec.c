#include "builtins.h"
#include "exec.h"
#include <stdlib.h>
#include <unistd.h>

void	clear_listed_env(t_env **listed_env)
{
	t_env	*head;

	head = *listed_env;
	if (head == NULL)
		return ;
	while (head)
	{
		free(head->key);
		free(head->value);
		free(head->full_line);
		free(head);
		*listed_env = (*listed_env)->next;
		head = *listed_env;
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
	clear_listed_env(&data->listed_env);
}
