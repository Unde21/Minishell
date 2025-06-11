#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

static char	*get_env_value(t_data *data, char *var_name, char **env,
		bool is_quote)
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
	{
		data->is_ambiguous = true;
		return (ft_strdup(""));
	}
	if (is_quote == true)
		env_value = ft_strdup(ft_strchr(env[i], '=') + 1);
	else
		env_value = dup_word_splitting(ft_strchr(env[i], '=') + 1);
	return (env_value);
}

void	join_with_expand_file(t_data *data, char **expanded, char *s, size_t *i)
{
	char	*var_name;
	char	*env_value;

	++(*i);
	var_name = get_var_name(&s[*i]);
	if (var_name == NULL)
	{
		free(var_name);
		ft_dprintf(2, ERR_MALLOC);
		return ;
	}
	env_value = get_env_value(data, var_name, data->env,
			data->cmd->args->is_quote);
	if (env_value == NULL)
	{
		free(var_name);
		free(env_value);
		if (data->is_ambiguous == false)
			ft_dprintf(2, ERR_MALLOC);
		return ;
	}
	*expanded = ft_strjoin_and_free(*expanded, env_value);
	*i += ft_strlen(var_name);
	free(var_name);
	free(env_value);
}
