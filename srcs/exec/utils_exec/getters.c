#include "exec.h"
#include "parsing.h"

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
	start = i + 1;
	len = 0;
	while (params[start + len])
		len++;
	value = malloc(len + 1);
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
	key = malloc(i + 1);
	if (!key)
		return (NULL);
	i = -1;
	while (env[++i] && env[i] != '=' && env[i] != '+')
		key[i] = env[i];
	key[i] = '\0';
	return (key);
}



char	*get_path_cmd(char **env_array, char **params, char *path_cmd,
		int *return_value)
{
	int		i;
	char	*path_value;
	char	**path;

	i = 0;
	path_value = NULL;
	while (env_array[++i])
		if (ft_strncmp(env_array[i], "PATH", 4) == 0)
			path_value = get_value(env_array[i]);
	if (!path_value)
		return (NULL);
	path = ft_split(path_value, ':');
	if (!path)
		return (NULL);
	i = -1;
	while (path[++i])
	{
		path[i] = ft_strjoin_and_free(path[i], "/");
		if (path[i] == NULL)
			return (NULL);
		path[i] = ft_strjoin_and_free(path[i], params[0]);
		if (path[i] == NULL)
			return (NULL);
		if (is_access_ok(path[i], return_value, &path_cmd))
		{
			free_all(path);
			free(path_value);
			return (path_cmd);
		}
	}
	free_all(path);
	return (NULL);
}
