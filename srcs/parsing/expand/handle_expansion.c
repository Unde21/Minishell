/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:08:21 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/18 18:42:12 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static	int	get_var_name(char *str, char **var_name)
{
	size_t	i;
	size_t	len_var;

	len_var = 0;
	i = 0;
	ft_printf("str: %s\n", str);
	if (ft_isalpha(str[len_var]) == 0 && str[len_var] != ASCII_UNDERSCORE)
		return (-1);
	while (str[len_var])
	{ 
		if (ft_isalpha(str[len_var]) == 0 && ft_isdigit(str[len_var]) == 0
			&& str[len_var] != ASCII_UNDERSCORE)
			break ;
		++len_var;
	}
	*var_name = malloc(sizeof(char) * (len_var + 1));
	if (*var_name == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return (-2);
	}
	while (str[i] && i < len_var)
	{
		(*var_name)[i] = str[i];
		++i;
	}
	ft_printf("var_name %s\n", *var_name);
	return (0);
}

static int	get_len_content_expanded(char **env_value, char *str, char **env)
{
	size_t	i;
	size_t	j;
	int		len_content;
	int		check_error;
	char	*var_name;
	char	*equal_sign;
	
	len_content = 0;
	var_name = NULL;
	i = 0;
	while (str[i] && str[i] != ASCII_DOLLAR)
		++i;
	if (str[i] == '\0')
		return (-1);
	++i;
	//TODO handle $? here if str[i + 1] == ? / else .... 
	check_error = get_var_name(&str[i], &var_name);
	ft_printf("len: %d\n", len_content);
	if (check_error != 0)
		return (check_error);
	j = 0;
	// ft_printf("%s\n", env[j]);
	// ft_printf("var_name : %s\n", var_name);
	ft_printf("len _var %d\n", (int)ft_strlen(var_name));
	while (env[j])
	{
		if (ft_strncmp(env[j], var_name, ft_strlen(var_name)) == 0
			&& env[j][ft_strlen(var_name)] == '=')
			break ;
		++j;
	}
	if (env[j] == NULL)
	{
		free(var_name);
		*env_value = ft_strdup("");
		return (ft_strlen(str));
	}
	equal_sign = ft_strchr(env[j], '=');
	if (equal_sign == NULL)
	{
		free(var_name);
		return (-1);
	}
	++equal_sign;
	*env_value = ft_strdup(equal_sign);
	if (*env_value == NULL)
	{
		free(var_name);
		ft_dprintf(2, ERR_MALLOC);
		return (-1);
	}
	while (str[i])
		++i;
	len_content = ft_strlen(str) - ft_strlen(var_name) - 1 + ft_strlen(*env_value);
	free(var_name);
	return (len_content);
}

static bool	expand(char *env_value, char *str, int len_content)
{
	char	*str_cpy;
	size_t	i;
	size_t	len_env;

	len_env = 0;
	i = 0;
	str_cpy = ft_strdup(str);
	if (str_cpy == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return (false);
	}
	free(str);
	str = malloc(sizeof(char) * (len_content + 1));
	if (str == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return (false);
	}
	while (str_cpy[i])
	{
		if (str_cpy[i] == ASCII_DOLLAR)
		{
			len_env = ft_strlcpy(&str[i], env_value, ft_strlen(env_value));
		}
		else if (str_cpy[i] != ASCII_DBLE_QUOTE)
			str[i + len_env] = str_cpy[i];
		++i;
	}
	return (true);
}

static bool	replace_env_variables(t_data *data, t_args *args)
{
	size_t	i;
	int		len_content;
	char	*env_value;
	
	env_value = NULL;
	len_content = 0;
	i = 0;
	while (args[i].content)
	{
		len_content = get_len_content_expanded(&env_value, args[i].content, data->env);
		if (len_content == -1)
		{
			ft_printf("yes\n");
			args->need_expand = false;
			return (false);
		}
		else if (len_content == -2)
			return (false);
		if (expand(env_value, args[i].content, len_content) == false)
		{
			free(env_value);
			return (false);
		}
		free(env_value);
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
	(void)data;
	while (current_cmd != NULL)
	{
		ft_printf("handle_expansion\n");
		while (i < current_cmd->nb_args)
		{
			if (current_cmd->args[i].need_expand == true)
				if (replace_env_variables(data, current_cmd->args) == false
					&& current_cmd->args[i].need_expand == true)
						return (false);
			++i;
		}
		current_cmd = current_cmd->next;
	}
	return (true);
}
