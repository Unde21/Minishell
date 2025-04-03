/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:34:25 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/03 12:44:52 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TODO delete print_lst
void	print_lst(t_token *token)
{
	if (token == NULL)
		return ;
	ft_printf("lst:");
	while(token->next)
	{
		ft_printf("-> %s", token->content);
		token = token->next;
	}
	ft_printf("-> %s -> NULL\n", token->content);
}
