#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_var_name(char *s)
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
		ft_dprintf(STDERR_FILENO, ERR_MALLOC);
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

static void	word_splitting_loop(char *src, char *dup, bool is_separator)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (ft_isspace(src[i]) == true)
			is_separator = true;
		while (ft_isspace(src[i]) == true)
			++i;
		if (is_separator == true)
		{
			is_separator = false;
			dup[j] = ' ';
		}
		else
		{
			dup[j] = src[i];
			++i;
		}
		++j;
	}
	dup[j] = '\0';
}

char	*dup_word_splitting(char *src)
{
	char	*dup;
	bool	is_separator;

	is_separator = false;
	dup = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dup == NULL)
		return (NULL);
	word_splitting_loop(src, dup, is_separator);
	return (dup);
}

static char	*get_env_value(char *var_name, t_env *listed_env, bool is_quote)
{
	char	*env_value;
	t_env	*current;
	size_t	len_var_name;

	current = listed_env;
	env_value = NULL;
	while (current != NULL)
	{
		len_var_name = ft_strlen(var_name);
		if (len_var_name != 0 && ft_strncmp(current->key,
				var_name, len_var_name) == 0)
			break ;
		current = current->next;
	}
	if (current == NULL)
		return (ft_strdup(""));
	if (is_quote == true)
		env_value = ft_strdup(current->value);
	else
		env_value = dup_word_splitting(current->value);
	return (env_value);
}

void	join_with_expand(t_data *data, char **expanded, char *s, size_t *i)
{
	char	*var_name;
	char	*env_value;

	++(*i);
	var_name = get_var_name(&s[*i]);
	if (var_name == NULL)
	{
		free(var_name);
		ft_dprintf(STDERR_FILENO, ERR_MALLOC);
		return ;
	}
	env_value = get_env_value(var_name, data->listed_env,
			data->cmd->args->is_quote);
	if (env_value == NULL)
	{
		free(var_name);
		free(env_value);
		ft_dprintf(STDERR_FILENO, ERR_MALLOC);
		return ;
	}
	*expanded = ft_strjoin_and_free(*expanded, env_value);
	*i += ft_strlen(var_name);
	free(var_name);
	free(env_value);
}
