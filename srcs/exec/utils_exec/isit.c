#include "exec.h"
#include "parsing.h"

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

bool	is_cmd(t_data *data)
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
		path[i] = ft_strjoin(path[i], data->cmd->args->content);
		if (access(path[i], F_OK | X_OK) == 0)
			return (true);
	}
	return (false);
}
