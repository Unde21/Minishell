#include "exec.h"
#include "parsing.h"
#include <stdlib.h>

static char	*search_path_in_env(t_data *data)
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
				if (data->return_value == 0)
					data->return_value = 127;
				return (NULL);
			}
			break ;
		}
		++i;
	}
	if (path_value == NULL)
		data->return_value = 127;
	return (path_value);
}

char	*get_strict_path(char **path, char **params, t_data *data)
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
			data->return_value = 1;
			free_all(path);
			return (NULL);
		}
		if (is_access_ok(path_value, path, data))
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

char	*get_path_cmd(t_data *data, char **params)
{
	char	*path_value;
	char	**path;

	path_value = search_path_in_env(data);
	if (path_value == NULL)
	{
		if (data->return_value == 0)
			data->return_value = 1;
		return (NULL);
	}
	path = ft_split(path_value, ':');
	free(path_value);
	path_value = NULL;
	if (!path)
	{
		data->return_value = 1;
		return (NULL);
	}
	return (get_strict_path(path, params, data));
}
