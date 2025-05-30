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
	data->return_value = 0;
	// exec_init(data);
	init_listed_env(data); //TODO sa leak si tu lance 2 appel a readline (a voir si tu as deja fix)
	if (ft_strcmp(data->cmd->params[0], "env") == 0)
		ft_env(data, data->cmd);
	if (ft_strcmp(data->cmd->params[0], "exit") == 0)
		ft_exit(data, data->cmd); // exit
	else if (ft_strcmp(data->cmd->params[0], "echo") == 0)
		ft_echo(data->cmd);
	else if (ft_strcmp(data->cmd->params[0], "pwd") == 0)
		ft_pwd(data, data->cmd);
	else if (ft_strcmp(data->cmd->params[0], "cd") == 0)
		ft_cd(data, data->cmd);
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

static void	prompt(t_data *data, char **str)
{
	char	*code;
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return ;
	code = ft_itoa(data->return_value);
	if (code != NULL)
	{
		if (data->return_value != 0)
			*str = RED CROSS;
		else
			*str = GREEN CHECK;
		*str = ft_strjoin(*str, code);
		*str = ft_strjoin_and_free(*str, END_RED);
		*str = ft_strjoin_and_free(*str, path);
		*str = ft_strjoin_and_free(*str, END_COLOR);
	}
	free(path);
	free(code);
}


static void	readline_loop(t_data *data)
{
	bool	error;
	char	*str;

	str = NULL;
	while (1)
	{
		error = false;
		prompt(data, &str);
		if (str == NULL)
		{
			error = true;
			str = RED "SEGFAULT$ " END_COLOR; //TODO je sais pas quoi mettre mais c est drole
		}
		data->line_read = readline(str);
		if (data->line_read == NULL)
			exit_with_right_value(data);
		add_history(data->line_read);
		handle_input(data);
		if (error == false)
			free(str);
		free(data->line_read);
	}
	free(str);
}

void	get_input(t_data *data)
{

	rl_catch_signals = 0;
	rl_event_hook = do_nothing;
	set_signal_action();
	readline_loop(data);
	rl_clear_history();
	free(data->line_read);
}
