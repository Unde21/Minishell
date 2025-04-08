/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:40:58 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/08 17:29:49 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parsing.h"
# include <stdio.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND_REDIR_IN,
	APPEND_REDIR_OUT
}		t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_token_lst
{
	t_token		*head;
	t_token		*tail;
}				t_token_lst;

typedef struct s_data
{
	char	*line_read;
	int		ac;
	char	*name_infile;
	char	*name_outfile;
	char	**av;
	char	**env;
}			t_data;

// init.c
void	init_data(t_data *data, int ac, char **av, char **env);

// utils.c
// TODO delete
void	print_lst(t_token *token);
int		wich_quote(int c);

#endif
