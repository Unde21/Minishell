#include "exec.h"

int	get_list_size(t_data *data)
{
	int	list_size;

	list_size = 0;
	while (data->cmd != NULL)
	{
		list_size++;
		data->cmd = data->cmd->next;
	}
	return (list_size);
}

char	*get_key(char *env)
{
	char	*key;
	int		i;

	key = NULL;
	i = 0;
	while (env[i] != '=')
		i++;
	key = malloc(i + 1);
	if (!key)
		return (NULL);
	i = -1;
	while (env[++i] != '=')
		key[i] = env[i];
	key[i] = '\0';
	return (key);
}

char	*get_random_name(char *here_doc)
{
	char	c;
	int		i;
	int		fd;

	i = 0;
	here_doc = malloc(sizeof(char) * 26);
	if (!here_doc)
		if (print_err("ERROR: malloc failed !\n") == false)
			return (NULL);
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
	{
		print_err("ERROR : opening /dev/random in get_random_name !\n");
		free(here_doc);
		return (NULL);
	}
	while (i < 25)
	{
		read(fd, &c, 1);
		if (ft_isprint(c) && c != '/')
			here_doc[i++] = c;
	}
	here_doc[i] = '\0';
	close(fd);
	return (here_doc);
}

char	*get_limiter(t_cmd *cmd)
{
	while (cmd->redir != NULL)
	{
		if (cmd->redir->type == HERE_DOC)
			return (cmd->redir->file);
		cmd->redir = cmd->redir->next;
	}
	return (NULL);
}

char	*get_path_cmd(char **params)
{
	int		i;
	char	**path;

	i = -1;
	path = ft_split(getenv("PATH"), ':');
	if (!path)
	{
		print_err("malloc failed\n");
		return (NULL);
	}
	while (path[++i])
	{
		path[i] = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(path[i], params[0]);
		if (access(path[i], X_OK) == 0)
			return (path[i]);
	}
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
	return (NULL);
}
