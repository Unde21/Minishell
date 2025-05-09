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
