#include "builtins.h"
#include "exec.h"
#include "minishell.h"
#include "parsing.h"

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

	if (!params || !params[0])
		return (0);
	key = get_key(params);
	if (!key)
		return (0);
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

char	**listed_env_to_array(t_env *listed_env)
{
	t_env	*head;
	char	**env_array;
	int		size;
	int		i;

	head = listed_env;
	size = lst_size(listed_env);
	env_array = malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		return (NULL);
	env_array[size] = NULL;
	i = -1;
	while (head)
	{
		env_array[++i] = ft_strdup(head->full_line);
		head = head->next;
	}
	return (env_array);
}
