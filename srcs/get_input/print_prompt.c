/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:30:49 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:30:50 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>

static bool	prompt_without_env(t_data *data, char **prompt)
{
	if (data->env == NULL || data->env[0] == NULL)
	{
		*prompt = ft_strdup("Minishell--> ");
		if (*prompt == NULL)
		{
			data->return_value = -1;
			return (print_err_false(ERR_MALLOC));
		}
		return (false);
	}
	return (true);
}

static void	create_prompt(t_data *data, char **prompt, char *code, char *path)
{
	if (data->return_value != 0)
		*prompt = ft_strdup(RED CROSS);
	else
		*prompt = ft_strdup(GREEN CHECK);
	if (*prompt == NULL)
	{
		data->return_value = -1;
		print_err_false(ERR_MALLOC);
		return ;
	}
	*prompt = ft_strjoin_and_free(*prompt, code);
	*prompt = ft_strjoin_and_free(*prompt, END_BLUE);
	*prompt = ft_strjoin_and_free(*prompt, path);
	*prompt = ft_strjoin_and_free(*prompt, END_COLOR);
	if (*prompt == NULL)
	{
		data->return_value = -1;
		print_err_false(ERR_MALLOC);
		return ;
	}
}

void	get_prompt(t_data *data, char **prompt)
{
	char	*code;
	char	*path;

	if (prompt_without_env(data, prompt) == false)
		return ;
	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		*prompt = NULL;
		return ;
	}
	code = ft_itoa(data->return_value);
	if (code != NULL)
	{
		create_prompt(data, prompt, code, path);
		free(code);
	}
	else
	{
		data->return_value = -1;
		print_err_false(ERR_MALLOC);
	}
	free(path);
}
