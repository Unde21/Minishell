#include "exec.h"
#include "minishell.h"
#include "parsing.h"

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

char	*get_value(char *env)
{
	char	*value;
	int		start;
	int		end;
	int		i;

	value = NULL;
	start = 0;
	end = 0;
	i = 0;
	while (env[i++] != '=')
		start++;
	while (env[i++])
		end++;
	start += 1;
	i = 0;
	value = malloc(end + 1);
	if (!value)
		return (NULL);
	while (env[start])
		value[i++] = env[start++];
	value[i] = '\0';
	return (value);
}
