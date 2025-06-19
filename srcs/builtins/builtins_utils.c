/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:29:34 by samaouch          #+#    #+#             */
/*   Updated: 2025/06/20 01:29:35 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset(t_env *listed_env)
{
	t_env	*reset;

	reset = listed_env;
	while (reset)
	{
		reset->printed = 0;
		reset = reset->next;
	}
}
