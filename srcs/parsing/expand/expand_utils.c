#include "parsing.h"
#include <stdlib.h>

static char	*get_var_name(char *s)
{
	size_t	i;
	int		len_var;
	char	*var_name;

	len_var = -1;
	i = 0;
	while (s[++len_var])
	{
		if (ft_isalpha(s[len_var]) == 0 && ft_isdigit(s[len_var]) == 0
			&& s[len_var] != ASCII_UNDERSCORE)
			break ;
	}
	var_name = malloc(sizeof(char) * (len_var + 1));
	if (var_name == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return (NULL);
	}
	while (s[i] && (int)i < len_var)
	{
		var_name[i] = s[i];
		++i;
	}
	var_name[i] = '\0';
	return (var_name);
}

static char	*get_env_value(char *var_name, char **env)
{
	char	*env_value;
	size_t	i;

	i = 0;
	env_value = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0
			&& env[i][ft_strlen(var_name)] == '=')
			break ;
		++i;
	}
	if (env[i] == NULL)
		return (ft_strdup(""));
	env_value = ft_strdup(ft_strchr(env[i], '=') + 1);
	return (env_value);
}

void	join_with_expand(char **env, char **expanded, char *s, size_t *i)
{
	char	*var_name;
	char	*env_value;

	++(*i);
	var_name = get_var_name(&s[*i]);
	if (var_name == NULL)
	{
		free(*expanded);
		free(var_name);
		ft_dprintf(2, ERR_MALLOC);
		return ;
	}
	env_value = get_env_value(var_name, env);
	if (env_value == NULL)
	{
		free(var_name);
		free(env_value);
		ft_dprintf(2, ERR_MALLOC);
		return ;
	}
	*expanded = ft_strjoin_and_free(*expanded, env_value);
	*i += ft_strlen(var_name);
	free(var_name);
	free(env_value);
}
