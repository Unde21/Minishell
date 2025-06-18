#include "exec.h"
#include "parsing.h"
#include <stdlib.h>

static char	*search_path_in_env(t_data *data, int *return_value)
{
	char	*path_value;
	size_t	i;

	i = 0;
	path_value = NULL;
	while (data->env_array[i])
	{
		if (ft_strncmp(data->env_array[i], "PATH=", 5) == 0)
		{
			path_value = get_value(data, data->env_array[i]);
			if (!path_value || path_value[0] == '\0')
			{
				if (*return_value == 0)
					*return_value = 127;
				return (NULL);
			}
			break ;
		}
		++i;
	}
	if (path_value == NULL)
		*return_value = 127;
	return (path_value);
}

char	*get_strict_path(char **path, char **params, int *return_value)
{
	char	*path_value;
	size_t	i;

	i = 0;
	while (path[i])
	{
		path_value = ft_strdup(path[i]);
		path_value = ft_strjoin_and_free(path_value, "/");
		path_value = ft_strjoin_and_free(path_value, params[0]);
		if (!path_value)
		{
			*return_value = 1;
			free_all(path);
			return (NULL);
		}
		if (is_access_ok(path_value, return_value, path))
		{
			free_all(path);
			return (path_value);
		}
		free(path_value);
		++i;
	}
	free_all(path);
	return (NULL);
}

char	*get_path_cmd(t_data *data, char **params, int *return_value)
{
	char	*path_value;
	char	**path;

	path_value = search_path_in_env(data, return_value);
	if (path_value == NULL)
	{
		if (*return_value == 0)
			*return_value = 1;
		return (NULL);
	}
	path = ft_split(path_value, ':');
	free(path_value);
	path_value = NULL;
	if (!path)
	{
		*return_value = 1;
		return (NULL);
	}
	return (get_strict_path(path, params, return_value));
}
