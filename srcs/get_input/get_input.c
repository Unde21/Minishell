#include "minishell.h"
#include "parsing.h"
#include "exec.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	clear_data(t_data *data)
{
	clear_cmd(data->cmd);
	clear_token(data->token_lst->head);
	free(data->token_lst);
	exit(130); // call notre propre exit
}

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signal_action(void)
{
	struct sigaction sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	handle_input(t_data *data)
{
	if (parsing(data) == false)
		return ;
	exec_init(data);
	clear_cmd(data->cmd);
	clear_token(data->token_lst->head);
	free(data->token_lst);
}

void	get_input(t_data *data)
{
	char	*str;
	char	*path;

	rl_catch_signals = 0;
	if (init_lst(data) == false)
		exit(1);  // call notre propre exit
	set_signal_action();
	// TODO Voir ce qu on met !
	path = getcwd(NULL, 0);
	str = ft_strjoin(path, "$ ");
	free(path);
	data->line_read = readline(str);
	if (data->line_read == NULL)
	{
		rl_clear_history();
		ft_printf("exit\n");
		clear_data(data);
	}
	add_history(data->line_read);
	while (data->line_read != NULL)
	{
		handle_input(data);
		free(data->line_read);
		data->line_read = readline(str);
		if (data->line_read == NULL)
		{
			rl_clear_history();
			ft_printf("exit\n");
			clear_data(data);
		}
		add_history(data->line_read);
	}
	rl_clear_history();
	free(data->line_read);
	free(str);
}
