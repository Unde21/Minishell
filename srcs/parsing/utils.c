/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:34:25 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/09 18:43:58 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO delete print_lst
void	print_lst(t_token *token)
{
	if (token == NULL)
		return ;
	ft_printf("\n");
	while (token->next)
	{
		ft_printf("-----------------\n{");
		ft_printf("%s}", token->content);
		ft_printf("\n-----------------\n");
		ft_printf("       |\n       v\n");
		token = token->next;
	}
	ft_printf("-----------------\n{");
	ft_printf("%s}", token->content);
	ft_printf("\n-----------------\n");
	ft_printf("       |\n       v\n");
	ft_printf("-----------------\n{NULL}");
	ft_printf("\n-----------------\n");
}

int	wich_quote(int c)
{
	if (c == ASCII_DBLE_QUOTE)
		return (ASCII_DBLE_QUOTE);
	else if (c == ASCII_SNGL_QUOTE)
		return (ASCII_SNGL_QUOTE);
	return (0);
}
