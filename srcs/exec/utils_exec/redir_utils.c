#include "exec.h"
#include "parsing.h"

bool	init_redir(t_data *data, t_cmd *cmd)
{
	while (cmd->redir)
	{
		if (cmd->redir->file == NULL)
		{
			ft_dprintf(2, PRINT_BASH);
			ft_dprintf(2, ERR_AMBIGUOUS);
			data->return_value = 1;
			return (false);
		}
		if (cmd->redir->type == REDIR_OUT)
		{
			cmd->fd_out = open(cmd->redir->file, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (cmd->fd_out < 0)
				return (print_err("ERROR: opening FD !\n"));
		}
		if (cmd->redir->type == APPEND)
		{
			cmd->fd_out = open(cmd->redir->file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (cmd->fd_out < 0)
				return (print_err("ERROR: opening FD !\n"));
		}
		if (cmd->redir->type == REDIR_IN)
		{
			cmd->fd_in = open(cmd->redir->file, O_RDONLY);
			if (cmd->fd_in < 0)
				return (print_err("ERROR: opening FD !\n"));
		}
		if (cmd->redir->type == HERE_DOC)
		{
			cmd->redir->file = heredoc(data, get_limiter(cmd));
			if (cmd->redir->file != NULL)
			{
				cmd->fd_in = open(cmd->redir->file, O_RDONLY);
				if (cmd->fd_in < 0)
					return (print_err("ERROR: opening FD !\n"));
				unlink(cmd->redir->file);
				free(cmd->redir->file);
			}
		}
		cmd->redir = cmd->redir->next;
	}
	return (true);
}