#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>

static void join_return_value(char **expanded, size_t *i, int prev_return_value)
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

static char	*expand(char *s, char **env, char *expanded, t_data *data)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ASCII_DOLLAR && wich_quote(&s[i]) != ASCII_SNGL_QUOTE
			&& s[i + 1] != ASCII_DOLLAR && s[i + 1] != '\0')
		{
			if (s[i + 1] == '?')
				join_return_value(&expanded, &i, data->prev_return_value);
			else
				join_with_expand(env, &expanded, s, &i);
		}
		else
			join_without_expand(&expanded, s[i], &i);
		if (expanded == NULL)
		{
			ft_dprintf(2, ERR_MALLOC);
			return (NULL);
		}
	}
	free(s);
	return (expanded);
}

static bool	replace_env_variables(t_data *data, t_args *args)
{
	char	*expanded;

	expanded = ft_calloc(sizeof(char), 1);
	if (expanded == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return (NULL);
	}
	args->content = expand(args->content, data->env, expanded, data);
	if (args->content == NULL)
	{
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
				if (replace_env_variables(data, &current_cmd->args[i]) == false
					&& current_cmd->args[i].need_expand == true)
					return (false);
			++i;
		}
		current_cmd = current_cmd->next;
	}
	return (true);
}
