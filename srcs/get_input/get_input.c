#include "builtins.h"
#include "exec.h"
#include "parsing.h"
#include <signal.h>
#include <stdlib.h>

int			g_return_value = 0;

static void	handle_input(t_data *data)
{
	if (ft_strcmp(data->line_read, "") == 0)
		return ;
	if (init_lst(data) == false)
	{
		data->return_value = 1;
		return ;
	}
	if (parsing(data) == false)
	{
		clear_cmd(data->cmd);
		clear_token(data->token_lst->head);
		free(data->token_lst);
		return ;
	}
	clear_token(data->token_lst->head);
	free(data->token_lst);
	exec(data);
	clear_cmd(data->cmd);
}

static void	exit_with_right_value(t_data *data, char *prompt)
{
	rl_clear_history();
	free(prompt);
	ft_printf("exit\n");
	free_listed_env(data);
	exit(data->return_value);
}

static bool	check_prompt_error(t_data *data, char **prompt)
{
	if (data->return_value == -1)
	{
		free_listed_env(data);
		return (false);
	}
	if (*prompt == NULL)
	{
		*prompt = ft_strdup(PATH_ERROR);
		if (*prompt == NULL)
		{
			data->return_value = 1;
			free_listed_env(data);
			return (print_err_false(ERR_MALLOC));
		}
	}
	return (true);
}

static void	readline_loop(t_data *data)
{
	char	*prompt;

	prompt = NULL;
	while (1)
	{
		set_signal_action();
		get_prompt(data, &prompt);
		if (check_prompt_error(data, &prompt) == false)
			exit(1);
		data->line_read = readline(prompt);
		if (data->line_read == NULL)
			exit_with_right_value(data, prompt);
		add_history(data->line_read);
		reset_g_return_value(data);
		free(prompt);
		handle_input(data);
		free(data->line_read);
	}
}

void	get_input(t_data *data)
{
	rl_catch_signals = 0;
	rl_event_hook = do_nothing;
	readline_loop(data);
	rl_clear_history();
}
