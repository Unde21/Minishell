

#include "minishell.h"
#include <stdlib.h>

static char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	len;
	size_t	j;

	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	join = malloc(sizeof(char) * (len + 1));
	if (!join)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		++j;
	}
	join[i + j] = '\0';
	free(s1);
	return (join);
}

static char	*get_var_name(char *s)
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
		ft_dprintf(2, ERR_MALLOC);
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

static char	*get_env_value(char *var_name, char **env)
{
	char	*env_value;
	size_t	i;

	i = 0;
	env_value = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0
			&& env[i][ft_strlen(var_name)] == '=')
			break ;
		++i;
	}
	if (env[i] == NULL)
		return (ft_strdup(""));
	env_value = ft_strdup(ft_strchr(env[i], '=') + 1);
	return (env_value);
}

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
			&& s[i + 1] != ASCII_DOLLAR)
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
