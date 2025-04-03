/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:40:58 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/03 12:43:20 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ERR_MALLOC "malloc failed\n"

typedef	enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT
} t_token_type;

typedef	struct s_token
{
	char	*content;
	t_token_type type;
	struct s_token *next;
} t_token;

typedef struct s_token_lst
{
	t_token *head;
	t_token *tail;
}	t_token_lst;
typedef struct s_data
{
	char	*line_read;
	int		ac;
	char	*name_infile;
	char	*name_outfile;
	char	**av;
	char	**env;
}	t_data;


// init.c
void	init_data(t_data *data, int ac, char **av, char **env);
// bool	init_token_lst(t_token_lst *tokens);

// parsing.c
void	get_input(t_data *data);
void	parsing(t_data *data);

// utils.c
//TODO delete
void	print_lst(t_token *token);

// handle_token.c
t_token *new_token(char *content, t_token_type type);
t_token_lst	*handle_token(char	*input, t_token_lst *tokens, t_token *current);

// handle_word.c
size_t	handle_word(char *input, t_token **new);

// create_node_for_token.c
size_t	handle_pipes(t_token **new);
size_t	handle_redir_out(t_token **new);
size_t	handle_redir_in(t_token **new);


#endif
