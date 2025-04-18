/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 08:26:15 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/18 10:32:48 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_expand(t_args *args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args[i].content)
	{
		j = 0;
		if (args[i].content[j] == ASCII_SNGL_QUOTE)
				args[i].is_quote = false;
		else
			args[i].is_quote = true;
		while (args[i].content[j])
		{
			if (args[i].content[j] == ASCII_DOLLAR
				&& args[i].is_quote == true)
				args[i].need_expand = true;
			++j;
		}
		++i;
	}
}

bool	expand_tokens(t_cmd *cmd)
{
	t_cmd	*current_cmd;

	current_cmd = cmd;
	while (current_cmd != NULL)
	{
		is_expand(current_cmd->args);
		current_cmd = current_cmd->next;
	}
	return (true);
}
