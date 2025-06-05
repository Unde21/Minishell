#include "builtins.h"
#include "exec.h"
#include "minishell.h"
#include "parsing.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int			g_return_value = 0;

static void	handle_input(t_data *data)
{
	if (g_return_value == CODE_SIGINT)
	{
		data->return_value = CODE_SIGINT;
		g_return_value = 0;
		return ;
	}
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
	data->return_value = 0;
	exec_init(data);
	clear_cmd(data->cmd);
	clear_token(data->token_lst->head);
	free(data->token_lst);
}

static int	do_nothing(void)
{
	return (0);
}

static void	exit_with_right_value(t_data *data, char *prompt)
{
	rl_clear_history();
	free(prompt);
	ft_printf("exit\n");
	free(data->line_read);
	exit(data->return_value);
}

static void	get_prompt(t_data *data, char **prompt)
{
	char	*code;
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		*prompt = NULL;
		return ;
	}
	code = ft_itoa(data->return_value);
	if (code != NULL)
	{
		if (data->return_value != 0)
			*prompt = ft_strdup(RED CROSS);
		else
			*prompt = ft_strdup(GREEN CHECK);
		*prompt = ft_strjoin_and_free(*prompt, code);	
		*prompt = ft_strjoin_and_free(*prompt, END_RED);
		*prompt = ft_strjoin_and_free(*prompt, path);
		*prompt = ft_strjoin_and_free(*prompt, END_COLOR);
	}
	free(path);
	free(code);
}

static void	readline_loop(t_data *data)
{
	char	*prompt;

	prompt = NULL;
	while (1)
	{
		get_prompt(data, &prompt);
		if (prompt == NULL)
		{
			prompt = ft_strdup(RED "SEGFAULT$ " END_COLOR);
			// TODO je sais pas quoi mettre mais c est drole
			if (prompt == NULL)
			{
				ft_dprintf(2, ERR_MALLOC);
				return ;
			}
		}
		data->line_read = readline(prompt);
		if (data->line_read == NULL)
			exit_with_right_value(data, prompt);
		add_history(data->line_read);
		handle_input(data);
		free(prompt);
		free(data->line_read);
	}
}

void	get_input(t_data *data)
{
	rl_catch_signals = 0;
	rl_event_hook = do_nothing;
	set_signal_action();
	readline_loop(data);
	rl_clear_history();
}
