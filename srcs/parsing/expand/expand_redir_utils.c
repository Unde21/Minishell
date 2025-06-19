#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>

static char	*handle_ambiguous_file(t_data *data, char *var_name)
{
	char	*tmp;

	data->ambiguous_file = ft_strdup("$");
	if (data->ambiguous_file == NULL)
	{
		ft_dprintf(STDERR_FILENO, ERR_MALLOC);
		return (NULL);
	}
	tmp = ft_strdup(data->ambiguous_file);
	free(data->ambiguous_file);
	data->ambiguous_file = ft_strjoin_and_free(tmp, var_name);
	if (data->ambiguous_file == NULL)
	{
		ft_dprintf(STDERR_FILENO, ERR_MALLOC);
		return (NULL);
	}	
	// if (data->ambiguous_file)
	// {
		// free(data->ambiguous_file);
		// data->ambiguous_file = NULL;
	// }
	data->is_ambiguous = true;
	return (NULL);
}

static char	*get_env_value(t_data *data, char *var_name, bool is_quote)
{
	char	*env_value;
	char	*tmp;
	t_env	*current;
	size_t	len_var_name;

	current = data->listed_env;
	env_value = NULL;
	while (current != NULL)
	{
		len_var_name = ft_strlen(var_name);
		if (len_var_name != 0 && ft_strncmp(current->key, var_name, len_var_name
				+ 1) == 0)
			break ;
		current = current->next;
	}
	if (current == NULL && data->is_heredoc == false)
		return (handle_ambiguous_file(data, var_name));
	if (is_quote == true)
		return (ft_strdup(current->value));
	tmp = ft_strdup(current->value);
	if (tmp == NULL)
		return (NULL);
	env_value = dup_word_splitting(tmp);
	free(tmp);
	return (env_value);
}

void	join_with_expand_file(t_data *data, char **expanded, char *s, size_t *i)
{
	char	*var_name;
	char	*env_value;

	var_name = get_var_name(&s[++*i]);
	if (var_name == NULL)
	{
		data->return_value = 1;
		ft_dprintf(STDERR_FILENO, ERR_MALLOC);
		return ;
	}
	env_value = get_env_value(data, var_name, data->cmd->args->is_quote);
	if (env_value == NULL)
	{
		free(var_name);
		if (data->is_ambiguous == false)
		{
			data->return_value = 1;
			ft_dprintf(STDERR_FILENO, ERR_MALLOC);
		}
		return ;
	}
	*expanded = ft_strjoin_and_free(*expanded, env_value);
	*i += ft_strlen(var_name);
	free(var_name);
	free(env_value);
}
