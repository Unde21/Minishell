#include "exec.h"
#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

void	reset(t_env *listed_env)
{
	t_env	*reset;

	reset = listed_env;
	while (reset)
	{
		reset->printed = 0;
		reset = reset->next;
	}
}

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

bool	is_key_valid(char *params)
{
	int	i;

	i = -1;
	if (!params || !(ft_isalpha(params[0]) || params[0] == '_'))
		return (false);
	while (params[++i])
	{
		if (params[i] == '=')
			break ;
		if (params[i] == '+' && params[i + 1] == '=')
			break ;
		if (!ft_isalnum(params[i]) && params[i] != '_')
			return (false);
	}
	return (true);
}

int	export_type(char *params, t_env *listed_env)
{
	char	*key;

	// if (!params || !params[0])
	// 	return (0); // Error return 0 ?
	key = get_key(params);
	if (!key)
		return (0); // Error return 0 ?
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

bool	append_export(t_env *listed_env, char *params)
{
	char	*key;
	char	*value;
	int		len_key;

	key = get_key(params); // Leak si MALLOC == NULL
	value = get_value(params); // Leak si MALLOC == NULL
	len_key = ft_strlen(key);
	while (listed_env)
	{
		if (ft_strncmp(key, listed_env->key, len_key) == 0)
		{
			listed_env->value = ft_strjoin_and_free(listed_env->value, value);
			if (listed_env->value == NULL)
				return (print_err_false(ERR_MALLOC));
			listed_env->full_line = ft_strjoin_and_free(listed_env->full_line,
					value);
			if (listed_env->full_line == NULL)
				return (print_err_false(ERR_MALLOC));
		}
		listed_env = listed_env->next;
	}
	return (true);
}
