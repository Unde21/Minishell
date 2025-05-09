#include "exec.h"

bool	is_heredoc(t_token *token)
{
	while (token != NULL)
	{
		if (ft_strcmp(token->content, "<<") == 0)
			return (true);
		token = token->next;
	}
	return (false);
}
void	exec_init(t_data *data)
{
	init_listed_env(data);
	if (is_heredoc(data->token_lst->head))
		heredoc_init(data);
	//////////////////////////
	//////////* DEBUG *///////
	//////////////////////////
	// ft_printf("\nline : {%s}\n\n", data->line_read);
	// print_lst(data->token_lst->head, 2);
	// print_lst_cmd(data->cmd);
	// print_lst_cmd_expand(data->cmd);
	// print_listed_env(data);
	// printf("here_doc name => %s\n here_doc len =>%ld\n\n", here_doc,
	// 	ft_strlen(here_doc));
	///////////////////////////
	///////////////////////////
	free_listed_env(data);
}
