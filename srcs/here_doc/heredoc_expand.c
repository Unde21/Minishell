/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:30:55 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:30:56 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

bool	is_expand_here_doc(char *file_name, char *line)
{
	size_t	i;

	i = 0;
	if (file_name == NULL)
		return (false);
	if (wich_quote(file_name) != NO_QUOTE)
		return (false);
	while (line[i])
	{
		if (line[i] == ASCII_DOLLAR)
			return (true);
		++i;
	}
	return (false);
}

static bool	duplicate_limiter(size_t *i, int quote, char *limiter, char **dup)
{
	size_t	index;
	char	*tmp;

	index = *i;
	while (limiter[index] != quote && limiter[index])
		++index;
	tmp = malloc(sizeof(char) * (index - *i + 1));
	if (tmp == NULL)
		return (false);
	index = 0;
	while (limiter[*i] != quote && limiter[*i])
	{
		tmp[index] = limiter[*i];
		++(*i);
		++index;
	}
	tmp[index] = '\0';
	*dup = ft_strjoin_and_free(*dup, tmp);
	free(tmp);
	if (*dup == NULL)
		return (false);
	return (true);
}

static bool	remove_quote_loop(char *limiter, char **dup)
{
	size_t	i;
	int		quote;

	i = 0;
	quote = wich_quote(limiter);
	while (limiter[i])
	{
		if (limiter[i] != quote)
		{
			if (duplicate_limiter(&i, quote, limiter, dup) == false)
				return (false);
		}
		else
			++i;
	}
	return (true);
}

char	*remove_quote_heredoc(t_data *data, char *limiter)
{
	char	*dup;

	if (wich_quote(limiter) == NO_QUOTE)
	{
		dup = ft_strdup(limiter);
		if (dup == NULL)
		{
			data->return_value = 1;
			return (print_err_null(ERR_MALLOC));
		}
		return (dup);
	}
	dup = ft_strdup("");
	if (dup == NULL)
	{
		data->return_value = 1;
		return (print_err_null(ERR_MALLOC));
	}
	if (remove_quote_loop(limiter, &dup) == true)
		return (dup);
	data->return_value = 1;
	if (dup != NULL)
		free(dup);
	return (print_err_null(ERR_MALLOC));
}
