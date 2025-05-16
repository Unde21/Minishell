#include "exec.h"
#include "parsing.h"

int	is_redir(t_data *data)
{
	while (data->cmd->redir != NULL)
	{
		if (data->cmd->redir->type == REDIR_IN)
			return (1);
		else if (data->cmd->redir->type == REDIR_OUT)
			return (2);
		data->cmd->redir = data->cmd->redir->next;
	}
	return (0);
}

bool	is_pipe(t_data *data)
{
	while (data->cmd->redir != NULL)
	{
		if (data->cmd->redir->type == PIPE)
			return (true);
		data->cmd->redir = data->cmd->redir->next;
	}
	return (false);
}

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

bool	is_cmd(t_data *data, char *cmd)
{
	char	**path;
	int		i;

	i = -1;
	path = ft_split(get_listed_env(data), ':');
	if (!path)
		return (print_err(ERR_MALLOC));
	while (path[++i])
		path[i] = ft_strjoin(path[i], "/");
	i = -1;
	while (path[++i])
	{
		path[i] = ft_strjoin(path[i], cmd);
		if (access(path[i], F_OK | X_OK) == 0)
			return (true);
	}
	return (false);
}
