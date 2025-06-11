#include "builtins.h"
#include "exec.h"
#include "minishell.h"
#include <stdlib.h>

void	print_export(t_data *data)
{
	int		list_size;
	t_env	*head;

	if (!data->listed_env)
		return ;
	list_size = get_list_size(data);
	head = data->listed_env;
	while (head)
	{
		if (ft_strcmp(head->key, head->next->key) > 0)
		{
			ft_printf("declare -x %s\n", data->listed_env->full_line);
			head = head->next;
			list_size--;
		}
		else
			head = data->listed_env->next;
		if (list_size == 1)
			return ;
	}
}

bool	is_valid_key(char *params)
{
	int	i;

	i = -1;
	while (params[++i])
	{
		if (ft_isalnum(params[i]) == 0 && params[i] != '_' && params[i] != '='
			&& (ft_strchr(params, '=') == NULL))
			return (false);
	}
	return (true);
}

static char	*get_name(char *params)
{
	int		i;
	int		len;
	char	*key;

	len = 0;
	i = -1;
	while (params[++i] != '=')
		len++;
	key = malloc(len + 1);
	if (!key)
		return (NULL);
	i = -1;
	while (params[++i] != '=')
		key[i] = params[i];
	key[i] = '\0';
	return (key);
}

static char	*get_value(char *params)
{
	char	*value;
	int		i;
	int		len;
	int		start;

	start = 0;
	len = 0;
	i = -1;
	value = NULL;
	while (params[++i] != '=')
		start++;
	len = i + 1;
	while (params[++i])
		len++;
	value = malloc(len + 1);
	if (!value)
		return (NULL);
	i = -1;
	while (params[++start])
		value[++i] = params[start];
	value[start] = '\0';
	return (value);
}

void	ft_export(t_data *data)
{
	t_env	*new_node;

	if (data->cmd->params[1] == NULL)
		print_export(data);
	if (!is_valid_key(data->cmd->params[1]))
		return ;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	else
	{
		new_node->key = get_name(data->cmd->params[1]);
		new_node->value = get_value(data->cmd->params[1]);
		new_node->full_line = ft_strdup(data->cmd->params[1]);
		new_node->next = NULL;
	}
	add_back(new_node, &data->listed_env);
}
