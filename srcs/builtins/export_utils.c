#include "exec.h"
#include "parsing.h"
#include <stdlib.h>

int	lst_size(t_env *head)
{
	int		count;
	t_env	*current;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

bool	is_key_valid(t_data *data, char *params)
{
	int	i;

	i = -1;
	if (!params || !(ft_isalpha(params[0]) || params[0] == '_'))
	{
		data->return_value = 1;
		return (false);
	}
	while (params[++i])
	{
		if (params[i] == '=')
			break ;
		if (params[i] == '+' && params[i + 1] == '=')
			break ;
		if (!ft_isalnum(params[i]) && params[i] != '_')
		{
			data->return_value = 1;
			return (false);
		}
	}
	return (true);
}

int	export_type(t_data *data, char *params, t_env *listed_env)
{
	char	*key;

	key = get_key(params);
	if (!key)
	{
		print_err_false(ERR_MALLOC);
		data->return_value = 1;
		return (-1);
	}
	while (listed_env)
	{
		if (ft_strcmp(key, listed_env->key) == 0)
		{
			free(key);
			return (2);
		}
		if (ft_strnstr(params, "+=", ft_strlen(key) + 2) != NULL)
		{
			free(key);
			return (3);
		}
		listed_env = listed_env->next;
	}
	free(key);
	return (1);
}

static bool	free_key_and_return_false(char *key, char *value)
{
	free(key);
	free(value);
	return (print_err_false(ERR_MALLOC));
}

bool	append_export(char *key, t_env *listed_env, char *params)
{
	char	*value;

	value = get_value(params);
	if (value == NULL)
	{
		free(key);
		return (print_err_false(ERR_MALLOC));
	}
	while (listed_env)
	{
		if (ft_strncmp(key, listed_env->key, ft_strlen(key)) == 0)
		{
			listed_env->value = ft_strjoin_and_free(listed_env->value, value);
			if (listed_env->value == NULL)
				return (free_key_and_return_false(key, value));
			listed_env->full_line = ft_strjoin_and_free(listed_env->full_line,
					value);
			if (listed_env->full_line == NULL)
				return (free_key_and_return_false(key, value));
		}
		listed_env = listed_env->next;
	}
	free(key);
	free(value);
	return (true);
}
