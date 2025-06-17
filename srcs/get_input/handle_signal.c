#include "minishell.h"
#include "parsing.h"
#include <fcntl.h>
#include <signal.h>

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_return_value = CODE_SIGINT;
		if (rl_readline_state & RL_STATE_COMPLETING)
		{
			rl_pending_input = 'n';
		}
		rl_replace_line("", 0);
		ft_printf("^C");
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

void	set_signal_action_child(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
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
