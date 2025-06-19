/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minimal_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:31:04 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:31:05 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include <stdlib.h>

static bool	fill_new_node(t_data *data, char *key, char *value, t_env *new)
{
	char	*tmp;

	new->key = ft_strdup(key);
	if (new->key == NULL)
	{
		data->return_value = 1;
		return (print_err_false(ERR_MALLOC));
	}
	new->value = ft_strdup(value);
	if (new->value == NULL)
	{
		data->return_value = 1;
		return (print_err_false(ERR_MALLOC));
	}
	tmp = ft_strdup(new->key);
	new->full_line = ft_strjoin_and_free(tmp, "=");
	new->full_line = ft_strjoin_and_free(new->full_line, new->value);
	if (new->full_line == NULL)
	{
		data->return_value = 1;
		return (print_err_false(ERR_MALLOC));
	}
	new->next = NULL;
	new->printed = 0;
	return (true);
}

static bool	fill_shlvl_node(t_data *data, t_env *new_node)
{
	char	*s_shell_lvl;
	int		shell_lvl;

	shell_lvl = 1;
	if (getenv("SHLVL") != NULL)
		shell_lvl = ft_atoi(getenv("SHLVL"), 0) + 1;
	s_shell_lvl = ft_itoa(shell_lvl);
	if (s_shell_lvl == NULL)
	{
		data->return_value = 1;
		return (print_err_false(ERR_MALLOC));
	}
	if (fill_new_node(data, "SHLVL", s_shell_lvl, new_node) == false)
	{
		free(s_shell_lvl);
		return (false);
	}
	free(s_shell_lvl);
	add_back(new_node, &data->listed_env);
	return (true);
}

bool	fill_next_node_minimal(t_data *data)
{
	t_env	*shell_lvl_node;
	t_env	*history_node;

	shell_lvl_node = malloc(sizeof(t_env));
	if (shell_lvl_node == NULL)
		return (print_err_false(ERR_MALLOC));
	if (fill_shlvl_node(data, shell_lvl_node) == false)
	{
		free(shell_lvl_node);
		return (false);
	}
	history_node = malloc(sizeof(t_env));
	if (history_node == NULL)
		return (print_err_false(ERR_MALLOC));
	if (fill_new_node(data, "_", "/usr/bin/env", history_node) == false)
	{
		free(history_node);
		return (false);
	}
	add_back(history_node, &data->listed_env);
	return (true);
}

bool	create_first_node(t_data *data, char *pwd)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		data->return_value = 1;
		return (false);
	}
	if (fill_new_node(data, "PWD", pwd, new_node) == false)
	{
		free(pwd);
		free(new_node);
		return (false);
	}
	data->listed_env = new_node;
	return (true);
}
