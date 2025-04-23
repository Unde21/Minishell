/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:08:21 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/23 19:29:34 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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

static	char	*get_var_name(char *s)
{
	size_t	i;
	size_t	len_var;
	char	*var_name;

	len_var = 0;
	i = 0;
	while (s[len_var])
	{ 
		if (ft_isalpha(s[len_var]) == 0 && ft_isdigit(s[len_var]) == 0
			&& s[len_var] != ASCII_UNDERSCORE)
			break ;
		++len_var;
	}
	var_name = malloc(sizeof(char) * (len_var + 1));
	if (var_name == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return (NULL);
	}
	while (s[i] && i < len_var)
	{
		var_name[i] = s[i];
		++i;
	}
	var_name[i] = '\0';
	return (var_name);
}


static	char	*get_env_value(char *var_name, char **env)
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

static char	*expand(char *s, char **env)
{
	char	*expanded;
	char	*var_name;
	char	*env_value;
	char	tmp[2];
	size_t	i;

	expanded = ft_calloc(sizeof(char), 1);
	if (expanded == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == ASCII_DOLLAR && wich_quote(&s[i]) != ASCII_SNGL_QUOTE)
		{
			++i;
			var_name = get_var_name(&s[i]);
			if (var_name == NULL)
			{
				free(expanded);
				free(var_name);
				ft_dprintf(2, ERR_MALLOC);
				return (NULL);
			}
			env_value = get_env_value(var_name, env);
			if (env_value == NULL)
			{
				free(var_name);
				free(env_value);
				ft_dprintf(2, ERR_MALLOC);
				return (NULL);
			}
			expanded = ft_strjoin_and_free(expanded,  env_value);
			if (expanded == NULL)
			{
				free(var_name);
				free(env_value);
				ft_dprintf(2, ERR_MALLOC);
				return (NULL);
			}
			i += ft_strlen(var_name);
			free(var_name);
			free(env_value);
		}
		else
		{
			tmp[0] = s[i];
			tmp[1] = '\0';
			expanded = ft_strjoin_and_free(expanded, tmp);
			if (expanded == NULL)
			{
				free(var_name);
				free(env_value);
				ft_dprintf(2, ERR_MALLOC);
				return (NULL);
			}
			++i;
		}
	}
	free(s);
	return (expanded);
}

static bool	replace_env_variables(t_data *data, t_args *args)
{
	size_t	i;
	int		len_content;
	
	len_content = 0;
	i = 0;
	while (args[i].content)
	{
		args[i].content = expand(args[i].content, data->env);
		if (args[i].content == NULL)
		{
			return (false);
		}
		++i;
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
