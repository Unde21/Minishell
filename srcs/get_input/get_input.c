#include "exec.h"
#include "minishell.h"
#include "parsing.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int			g_return_value;

static void	exit_with_right_value(t_data *data)
{
	rl_clear_history();
	data->prev_return_value = 0;
	ft_printf("exit\n");
	exit(data->prev_return_value);
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_return_value = 130;
		ft_dprintf(0, "^C");
		if (rl_readline_state & RL_STATE_COMPLETING)
			rl_pending_input = 'n';
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

static void	set_signal_action(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	handle_input(t_data *data)
{
	if (init_lst(data) == false)
		return ;
	if (parsing(data) == false)
	{
		clear_cmd(data->cmd);
		clear_token(data->token_lst->head);
		free(data->token_lst);
		return ;
	}
	exec_init(data);
	clear_cmd(data->cmd);
	clear_token(data->token_lst->head);
	free(data->token_lst);
}

int	do_nothing(void)
{
	return (0);
}
void	get_input(t_data *data)
{
	char	*str;
	char	*path;

	rl_catch_signals = 0;
	rl_event_hook = do_nothing;
	set_signal_action();
	path = getcwd(NULL, 0); // TODO Voir ce qu on met !
	str = ft_strjoin(path, "$ ");
	free(path);
	data->line_read = readline(str);
	if (data->line_read == NULL)
		exit_with_right_value(data);
	add_history(data->line_read);
	while (data->line_read != NULL)
	{
		handle_input(data);
		free(data->line_read);
		data->line_read = readline(str);
		if (data->line_read == NULL)
			exit_with_right_value(data);
		add_history(data->line_read);
	}
	rl_clear_history();
	free(data->line_read);
	free(str);
}
