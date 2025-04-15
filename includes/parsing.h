/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samaouch <samaouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:16:05 by samaouch          #+#    #+#             */
/*   Updated: 2025/04/15 18:32:37 by samaouch         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"
# include <readline/history.h>
# include <readline/readline.h>

# define ERR_MALLOC "malloc failed\n"
# define MISS_DBLE_QUOTE "syntax error: missing closing double quote\n"
# define MISS_SNGL_QUOTE "syntax error: missing closing single quote\n"
# define ERR_NO_FILE "syntax error: missing file after redirection\n" //TODO make better
# define ASCII_DBLE_QUOTE 34
# define ASCII_SNGL_QUOTE 39
# define NO_QUOTE 0

struct						s_cmd;
struct						s_data;
struct						s_token;
struct						s_token_lst;
enum						e_token_type;

typedef struct s_cmd		t_cmd;
typedef struct s_data		t_data;
typedef struct s_token		t_token;
typedef struct s_token_lst	t_token_lst;
typedef enum e_token_type	t_token_type;

// parsing.c
void		get_input(t_data *data);
void		parsing(t_data *data);

// handle_token.c
t_token		*new_token(char *content, t_token_type type);
bool	handle_token(char *input, t_token_lst *tokens, t_token *current);

// handle_word.c
size_t		handle_word(char *input, t_token **new, bool *error);

// create_node_for_token.c
size_t		new_node_pipes(t_token **new);
size_t		new_node_redir_out(t_token **new);
size_t		new_node_redir_in(t_token **new);
size_t		new_node_here_doc(t_token **new);
size_t		new_node_append(t_token **new);

//fill_cmd_lst.c
bool get_cmd_args(t_token *current, t_cmd *cmd);

//parser.c
void	parser(t_data *data, t_cmd *cmd);

//fill_special_operator_cmd.c
bool add_special_operator_to_cmd(t_token *current, t_cmd *cmd);
bool fill_cmd_special_operator(t_token **current, t_cmd *current_cmd);


#endif
