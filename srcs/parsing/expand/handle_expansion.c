#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

static void	join_return_value(char **expanded, size_t *i, int prev_return_value)
{
	char	*str_return_value;

	str_return_value = ft_itoa(prev_return_value);
	if (str_return_value == NULL)
	{
		*expanded = NULL;
		return ;
	}
	++(*i);
	*expanded = ft_strjoin_and_free(*expanded, str_return_value);
	++(*i);
	free(str_return_value);
}

static void	join_without_expand(char **expanded, char c, size_t *i)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	*expanded = ft_strjoin_and_free(*expanded, tmp);
	++(*i);
}

static char	*expand(char *s, char *expanded, t_data *data)
{
	size_t	i;

	i = 0;
	if (s[i] == ASCII_DBLE_QUOTE)
		data->cmd->args->is_quote = true;
	while (s[i])
	{
		if (s[i] == ASCII_DOLLAR && s[i + 1] != ASCII_DOLLAR)
		{
			if (s[i + 1] == '?')
				join_return_value(&expanded, &i, data->return_value);
			else
				join_with_expand(data, &expanded, s, &i);
		}
		else if (s[i] == ASCII_DBLE_QUOTE)
			++i;
		else
			join_without_expand(&expanded, s[i], &i);
		if (expanded == NULL)
			break ;
	}
	free(s);
	if (expanded == NULL)
		return (NULL);
	return (expanded);
}

static bool	replace_env_variables(t_data *data, t_args *args)
{
	char	*expanded;

	expanded = ft_calloc(sizeof(char), 1);
	if (expanded == NULL)
	{
		data->return_value = 1;
		ft_dprintf(2, ERR_MALLOC);
		return (NULL);
	}
	data->cmd->args->is_quote = false;
	args->content = expand(args->content, expanded, data);
	if (args->content == NULL)
	{
		data->return_value = 1;
		ft_dprintf(2, ERR_MALLOC);
		return (false);
	}
	return (true);
}

bool	handle_expansion(t_data *data, t_cmd *cmd)
{
	t_cmd	*current_cmd;
	size_t	i;

	i = 0;
	current_cmd = cmd;
	while (current_cmd != NULL)
	{
		i = 0;
		while (i < current_cmd->nb_args)
		{
			if (current_cmd->args[i].need_expand == true)
			{
				if (replace_env_variables(data, &current_cmd->args[i]) == false
					&& current_cmd->args[i].need_expand == true)
					return (false);
			}
			else if (remove_quote(&current_cmd->args[i]) == false)
				return (false);
			++i;
		}
		current_cmd = current_cmd->next;
	}
	return (true);
}
