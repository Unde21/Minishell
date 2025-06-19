/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:30:27 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:30:28 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_size_cmd(t_cmd *cmd)
{
	size_t	size;
	t_cmd	*current;

	size = 0;
	current = cmd;
	while (current != NULL)
	{
		++size;
		current = current->next;
	}
	return (size);
}
