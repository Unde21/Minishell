#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

static char *handle_ambiguous_file(t_data *data, char *var_name)
{
	data->ambiguous_file = ft_strdup("$");
	if (data->ambiguous_file == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return (NULL);
	}
	data->ambiguous_file = ft_strjoin_and_free(data->ambiguous_file, var_name);
	if (data->ambiguous_file == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return (NULL);
	}
	data->is_ambiguous = true;
	return (NULL);
}

static char	*get_env_value(t_data *data, char *var_name, bool is_quote)
{
	char	*env_value;
	size_t	i;
	t_env	*current;

	current = data->listed_env;
	i = 0;
	env_value = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, var_name, ft_strlen(var_name)) == 0)
			break ;
		current = current->next;
	}
	if (current == NULL)
		return (handle_ambiguous_file(data, var_name));
	if (is_quote == true)
		env_value = ft_strdup(ft_strchr(current->full_line, '=') + 1);
	else
		env_value = dup_word_splitting(ft_strchr(current->full_line, '=') + 1);
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
	env_value = get_env_value(data, var_name, data->cmd->args->is_quote);
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
