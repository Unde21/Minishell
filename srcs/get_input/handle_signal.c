#include "minishell.h"
#include "parsing.h"
#include <signal.h>
#include <fcntl.h>

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_return_value = CODE_SIGINT;
		if (rl_readline_state & RL_STATE_COMPLETING)
		{
			rl_pending_input = 'n';
		}
		ft_printf("^C");
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

void	set_signal_action(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	signal_handler_child(int signal)
{
	if (signal == SIGINT)
		ft_printf("\n");
	if (signal == SIGQUIT)
		ft_printf("Quit (core dumped)\n");
}

void	reset_signal(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &signal_handler_child;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
