#include "exec.h"
#include "parsing.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char	*get_value(char *params)
{
	char	*value;
	int		start;
	int		len;
	int		i;
	int		j;

	if (!params)
		return (NULL);
	i = 0;
	while (params[i] && params[i] != '=')
		i++;
	if (!params[i] || params[i + 1] == '\0')
		return (ft_strdup("")); // faut checker si il foirre dans tout les appels de get_value
	start = i + 1;
	len = 0;
	while (params[start + len])
		len++;
	value = malloc(len + 1); // Leak si MALLOC == NULL
	if (!value)
		return (NULL);
	j = 0;
	while (params[start])
		value[j++] = params[start++];
	value[j] = '\0';
	return (value);
}

char	*get_key(char *env)
{
	char	*key;
	int		i;

	key = NULL;
	i = 0;
	while (env[i] && env[i] != '=' && env[i] != '+')
		i++;
	if (env[i] == '\0')
		return (ft_strdup(env));
	key = malloc(sizeof(char) * (i + 1)); // Leak si MALLOC == NULL
	if (!key)
	{
		print_err(ERR_MALLOC);
		return (NULL);
	}
	i = -1;
	while (env[++i] && env[i] != '=' && env[i] != '+')
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
	{
		print_err(ERR_MALLOC);
		return (NULL);
	}
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

char	*get_path_cmd(char **params, char *path_cmd, int *return_value)
{
	int		i;
	char	**path;

	i = -1;
	path = ft_split(getenv("PATH"), ':');
	if (!path)
	{
		*return_value = 1;
		return (NULL);
	}
	while (path[++i])
	{
		path[i] = ft_strjoin_and_free(path[i], "/");
		if (path[i] == NULL)
		{
			*return_value = 1;
			return (NULL);
		}
		path[i] = ft_strjoin_and_free(path[i], params[0]);
		if (path[i] == NULL)
		{
			*return_value = 1;
			return (NULL);
		}
		if (is_access_ok(path[i], return_value))
		{
			path_cmd = ft_strdup(path[i]);
			if (path_cmd == NULL)
				*return_value = 1;
			free_all(path);
			return (path_cmd);
		}
	}
	free_all(path);
	return (NULL);
}
