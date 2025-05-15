#include "exec.h"

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
		if (ft_isprint(c))
			here_doc[i++] = c;
	}
	here_doc[i] = '\0';
	close(fd);
	return (here_doc);
}

char	*get_limiter(t_data *data)
{
	while (data->cmd->redir != NULL)
	{
		if (data->cmd->redir->type == HERE_DOC)
			return (data->cmd->redir->file);
		data->cmd->redir = data->cmd->redir->next;
	}
	return (NULL);
}

char	*get_listed_env(t_data *data)
{
	char *path;

	path = NULL;
	while (data->listed_env != NULL)
	{
		if (ft_strcmp(data->listed_env->key, "PATH") == 0)
			path = data->listed_env->value;
		data->listed_env = data->listed_env->next;
	}
	return (path);
}