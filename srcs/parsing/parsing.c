/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 08:46:37 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/03 12:40:04 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	parsing(t_data *data)
{
	t_token_lst *tokens;
	t_token		*current;
	
	tokens = malloc(sizeof(t_token_lst));
	if (tokens == NULL)
	{
		ft_dprintf(2, ERR_MALLOC);
		return ;
	}
	tokens->head = NULL;
	tokens->tail = NULL;
	current = NULL;
	handle_token(data->line_read, tokens, current);
	print_lst(tokens->head);
}
