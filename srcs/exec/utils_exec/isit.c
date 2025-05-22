#include "exec.h"
#include "parsing.h"

char	*wich_redir(t_cmd *cmd)
{
	while (cmd->redir != NULL)
	{
		if (cmd->redir->type == REDIR_IN)
			return (cmd->redir->file);
		else if (cmd->redir->type == REDIR_OUT)
			return (cmd->redir->file);
		else if (cmd->redir->type == HERE_DOC)
			return (heredoc(get_limiter(cmd)));
		else
			return (NULL);
		cmd->redir = cmd->redir->next;
	}
	return (NULL);
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
