#include "builtins.h"
#include "exec.h"
#include "minishell.h"
#include "parsing.h"

static void	export_new(t_env *listed_env, char *params)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	else
	{
		new_node->key = get_key(params);
		new_node->value = get_value(params);
		new_node->full_line = ft_strdup(params);
		new_node->printed = 0;
		new_node->next = NULL;
	}
	add_back(new_node, &listed_env);
}

static void	export_old(t_env *listed_env, char *params)
{
	char	*key;

	key = get_key(params);
	while (listed_env)
	{
		if (ft_strcmp(listed_env->key, key) == 0)
		{
			listed_env->value = get_value(key);
			listed_env->full_line = ft_strdup(params);
		}
		listed_env = listed_env->next;
	}
}

static void	append_export(t_env *listed_env, char *params)
{
	char	*key;
	char	*value;
	int		len_key;

	key = get_key(params);
	value = get_value(params);
	len_key = ft_strlen(key);
	while (listed_env)
	{
		if (ft_strncmp(key, listed_env->key, len_key) == 0)
		{
			listed_env->value = ft_strjoin_and_free(listed_env->value, value);
			listed_env->full_line = ft_strjoin_and_free(listed_env->full_line,
					value);
		}
		listed_env = listed_env->next;
	}
}

static void	export_no_argument(t_env *listed_env)
{
	int		printed_count;
	int		total;
	t_env	*head;
	t_env	*min;

	printed_count = 0;
	total = lst_size(listed_env);
	while (printed_count++ < total)
	{
		head = listed_env;
		min = NULL;
		while (head)
		{
			if (!head->printed && (!min || strcmp(head->key, min->key) < 0))
				min = head;
			head = head->next;
		}
		if (min)
		{
			printf("export %s \n", min->full_line);
			min->printed = 1;
		}
	}
	reset(listed_env);
}

void	ft_export(t_data *data)
{
	int	i;
	int	type;

	i = 0;
	type = 0;
	if (data->cmd->params[1] == NULL)
		export_no_argument(data->listed_env);
	while (data->cmd->params[++i])
	{
		if (!is_key_valid(data->cmd->params[i]))
		{
			ft_putstr_fd("export: `", STDERR_FILENO);
			ft_putstr_fd(data->cmd->params[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			data->return_value = 1;
			continue ;
		}
		type = export_type(data->cmd->params[i], data->listed_env);
		if (type == 1)
			export_new(data->listed_env, data->cmd->params[i]);
		else if (type == 2)
			export_old(data->listed_env, data->cmd->params[i]);
		else if (type == 3)
			append_export(data->listed_env, data->cmd->params[i]);
	}
}
