/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 09:34:25 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/11 16:37:51 by samaouch         ###   ########lyon.fr   */
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
		ft_printf("--------------------------------------------------------------------\n{");
		if (token->type == 0)
			ft_printf("%s}		type: WORD", token->content);
		else if (token->type == 1)
			ft_printf("%s}		type: SNGL_QUOTE", token->content);
		else if (token->type == 2)
			ft_printf("%s}		type: DBLE_QUOTE", token->content);
		else if (token->type == 3)
			ft_printf("%s}		type: PIPE", token->content);
		else if (token->type == 4)
			ft_printf("%s}		type: REDIR_IN", token->content);
		else if (token->type == 5)
			ft_printf("%s}		type: REDIR_OUT", token->content);
		else if (token->type == 6)
			ft_printf("%s}		type: HERE_DOC", token->content);
		else if (token->type == 7)
			ft_printf("%s}		type: APPEND", token->content);
		ft_printf("\n--------------------------------------------------------------------\n");
		ft_printf("       				|\n      				v\n");
		token = token->next;
	}
	ft_printf("--------------------------------------------------------------------\n{");
	if (token->type == 0)
		ft_printf("%s}		type: WORD", token->content);
	else if (token->type == 1)
		ft_printf("%s}		type: SNGL_QUOTE", token->content);
	else if (token->type == 2)
		ft_printf("%s}		type: DBLE_QUOTE", token->content);
	else if (token->type == 3)
		ft_printf("%s}		type: PIPE", token->content);
	else if (token->type == 4)
		ft_printf("%s}		type: REDIR_IN", token->content);
	else if (token->type == 5)
		ft_printf("%s}		type: REDIR_OUT", token->content);
	else if (token->type == 6)
		ft_printf("%s}		type: HERE_DOC", token->content);
	else if (token->type == 7)
		ft_printf("%s}		type: APPEND", token->content);
	ft_printf("\n--------------------------------------------------------------------\n");
	ft_printf("       				|\n       				v\n");
	ft_printf("--------------------------------------------------------------------\n{NULL}");
	ft_printf("\n--------------------------------------------------------------------\n");
}

int	wich_quote(int c)
{
	if (c == ASCII_DBLE_QUOTE)
		return (ASCII_DBLE_QUOTE);
	else if (c == ASCII_SNGL_QUOTE)
		return (ASCII_SNGL_QUOTE);
	return (0);
}
