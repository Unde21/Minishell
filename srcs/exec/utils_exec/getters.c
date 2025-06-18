#include "exec.h"
#include "parsing.h"
#include <stdlib.h>

char	*get_value(t_data *data, char *params)
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
	{
		value = ft_strdup("");
		if (value == NULL)
			data->return_value = 1;
		return (value);
	}
	start = i + 1;
	len = 0;
	while (params[start + len])
		len++;
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
	{
		data->return_value = 1;
		return (NULL);
	}
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
	char	*env_dup;

	key = NULL;
	i = 0;
	while (env[i] && env[i] != '=' && env[i] != '+')
		i++;
	if (env[i] == '\0')
	{
		env_dup = ft_strdup(env);
		if (!env_dup)
			return (print_err_null(ERR_MALLOC));
	}
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = -1;
	while (env[++i] && env[i] != '=' && env[i] != '+')
		key[i] = env[i];
	key[i] = '\0';
	return (key);
}

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
