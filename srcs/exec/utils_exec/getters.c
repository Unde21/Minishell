#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

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
		return (ft_strdup(""));
	// faut checker si il foirre dans tout les appels de get_value
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

char	**listed_env_to_array(t_data *data, t_env *listed_env)
{
	int		i;
	int		size;
	t_env	*head;

	i = -1;
	size = lst_size(listed_env);
	head = listed_env;
	data->env_array = malloc(sizeof(char *) * (size + 1));
	if (!data->env_array)
		return (NULL);
	data->env_array[size] = NULL;
	while (head)
	{
		data->env_array[++i] = ft_strdup(head->full_line);
		head = head->next;
	}
	return (data->env_array);
}

char	*get_path_cmd(t_data *data, char **params, int *return_value)
{
	int		i;
	char	*path_value;
	char	**path;

	path_value = NULL;
	i = -1;
	while (data->env_array[++i])
		if (ft_strncmp(data->env_array[i], "PATH=", 5) == 0)
			path_value = get_value(data->env_array[i]);
	if (!path_value)
	{
		*return_value = 127;
		return (NULL);
	}
	path = ft_split(path_value, ':');
	free(path_value);
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		path[i] = ft_strjoin_and_free(path[i], "/");
		if (!path[i])
		{
			free_all(path);
			return (NULL);
		}
		path[i] = ft_strjoin_and_free(path[i], params[0]);
		if (!path[i])
		{
			free_all(path);
			return (NULL);
		}
		if (is_access_ok(path[i], return_value))
		{
			path_value = ft_strdup(path[i]);
			free_all(path);
			return (path_value);
		}
	}
	free_all(path);
	return (NULL);
}
