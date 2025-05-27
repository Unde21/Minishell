#include "exec.h"
#include "minishell.h"
#include "parsing.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


#include "builtins.h"
int	g_return_value = 0;

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
	// exec_init(data);
	init_listed_env(data);
	if (ft_strcmp(data->cmd->params[0], "env") == 0)
		ft_env(data, data->cmd);
	clear_cmd(data->cmd);
	clear_token(data->token_lst->head);
	free(data->token_lst);
}

static int	do_nothing(void)
{
	return (0);
}

static void	exit_with_right_value(t_data *data)
{
	rl_clear_history();
	ft_printf("exit\n");
	exit(data->return_value);
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
	while (1)
	{
		data->line_read = readline(str);
		if (data->line_read == NULL)
			exit_with_right_value(data);
		add_history(data->line_read);
		handle_input(data);
		free(data->line_read);
	}
	rl_clear_history();
	free(data->line_read);
	free(str);
}

void	clear_all_data(t_data *data)
{
	clear_cmd(data->cmd);
	clear_token(data->token_lst->head);
	free(data->token_lst);
	free(data->line_read);
}
