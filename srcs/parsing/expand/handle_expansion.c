/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:31:30 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:31:31 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>

void	join_return_value(char **expanded, size_t *i, int prev_return_value)
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

void	join_without_expand(char **expanded, char c, size_t *i)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	*expanded = ft_strjoin_and_free(*expanded, tmp);
	++(*i);
}

static void	expand_loop(char *s, char **expanded, t_data *data, size_t *i)
{
	if (s[*i] == ASCII_DOLLAR && s[*i + 1] != ASCII_DOLLAR && s[*i + 1] != '\0')
	{
		if (s[*i + 1] == '?')
			join_return_value(expanded, i, data->return_value);
		else
			join_with_expand(data, expanded, s, i);
	}
	else if ((s[*i] == WILDCARDS || s[*i + 1] == WILDCARDS)
		&& data->cmd->args->is_quote == false)
		join_wildcards(data, expanded, s, i);
	else if (s[*i] == ASCII_DBLE_QUOTE)
		++(*i);
	else
		join_without_expand(expanded, s[*i], i);
}

static char	*expand(char *s, char *expanded, t_data *data, size_t pos)
{
	size_t	i;

	i = 0;
	if (s[i] == ASCII_DBLE_QUOTE)
	{
		data->cmd->args->is_quote = true;
		data->cmd->args[pos].is_quote = true;
	}
	while (s[i])
	{
		expand_loop(s, &expanded, data, &i);
		if (expanded == NULL)
			break ;
	}
	free(s);
	if (expanded == NULL)
		return (NULL);
	return (expanded);
}

bool	replace_env_variables(t_data *data, char **params, size_t i)
{
	char	*expanded;

	expanded = ft_calloc(sizeof(char), 1);
	if (expanded == NULL)
	{
		data->return_value = 1;
		return (print_err_false(ERR_MALLOC));
	}
	data->cmd->args->is_quote = false;
	*params = expand(*params, expanded, data, i);
	if (*params == NULL)
	{
		data->return_value = 1;
		if (data->error_readdir == false)
			ft_dprintf(STDERR_FILENO, ERR_MALLOC);
		else
			ft_dprintf(STDERR_FILENO, ERR_READDIR);
		return (false);
	}
	return (true);
}
