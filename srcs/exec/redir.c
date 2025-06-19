#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include <fcntl.h>
#include <unistd.h>

static bool	redir_out(t_cmd *cmd)
{
	if (cmd->redir->type == REDIR_OUT)
	{
		cmd->fd_out = open(cmd->redir->file, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (cmd->fd_out < 0)
			return (print_err_false(ERR_OP_FD));
	}
	if (cmd->redir->type == APPEND)
	{
		cmd->fd_out = open(cmd->redir->file, O_WRONLY | O_CREAT | O_APPEND,
				0644);
		if (cmd->fd_out < 0)
			return (print_err_false(ERR_OP_FD));
	}
	return (true);
}

static bool	redir_in(t_data *data, t_cmd *cmd)
{
	if (cmd->redir->type == REDIR_IN)
	{
		cmd->fd_in = open(cmd->redir->file, O_RDONLY);
		if (cmd->fd_in < 0)
			return (print_err_false(ERR_OP_FD));
	}
	if (cmd->redir->type == HERE_DOC)
	{
		cmd->redir->file = heredoc(data, cmd->redir, get_limiter(cmd));
		reset_signal();
		if (cmd->redir->file != NULL)
		{
			cmd->fd_in = open(cmd->redir->file, O_RDONLY);
			if (cmd->fd_in < 0)
			{
				data->return_value = 1;
				unlink(cmd->redir->file);
				return (print_err_false(ERR_OP_FD));
			}
			unlink(cmd->redir->file);
		}
	}
	return (true);
}

bool	init_redir(t_data *data, t_cmd *cmd)
{
	t_redir	*head;

	head = cmd->redir;
	while (cmd->redir)
	{
		if (cmd->redir->is_ambiguous)
		{
			print_ambiguous(data->ambiguous_file);
			data->return_value = 1;
			return (false);
		}
		if (redir_out(cmd) == false)
		{
			cmd->redir = head;
			data->return_value = 1;
			return (false);
		}
		if (redir_in(data, cmd) == false)
		{
			cmd->redir = head;
			data->return_value = 1;
			return (false);
		}
		cmd->redir = cmd->redir->next;
	}
	cmd->redir = head;
	return (true);
}
