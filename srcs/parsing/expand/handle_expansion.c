#include "minishell.h"
#include <stdlib.h>

static void	join_with_expand(char **env, char **expanded, char *s, size_t *i)
{
	char	*var_name;
	char	*env_value;

	++(*i);
	var_name = get_var_name(&s[*i]);
	if (var_name == NULL)
	{
		free(*expanded);
		free(var_name);
		ft_dprintf(2, ERR_MALLOC);
		return ;
	}
	env_value = get_env_value(var_name, env);
	if (env_value == NULL)
	{
		free(var_name);
		free(env_value);
		ft_dprintf(2, ERR_MALLOC);
		return ;
	}
	*expanded = ft_strjoin_and_free(*expanded, env_value);
	*i += ft_strlen(var_name);
	free(var_name);
	free(env_value);
}

static void	join_without_expand(char **expanded, char c, size_t *i)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	*expanded = ft_strjoin_and_free(*expanded, tmp);
	++(*i);
}

static char	*expand(char *s, char **env, char *expanded)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ASCII_DOLLAR && wich_quote(&s[i]) != ASCII_SNGL_QUOTE
			&& s[i + 1] != ASCII_DOLLAR && s[i + 1] != '\0')
		{
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
	args->content = expand(args->content, data->env, expanded);
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
