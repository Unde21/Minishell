#include "minishell.h"
#include "parsing.h"
#include <signal.h>
#include <fcntl.h>

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_return_value = CODE_SIGINT;
		// ft_dprintf(0, "^C");
		if (rl_readline_state & RL_STATE_COMPLETING)
		{
			rl_pending_input = 'n';
		}
		rl_replace_line("", 0);
		rl_done = 1;
	}
}

void	set_signal_action(void)
{
	struct sigaction	sa;

	g_return_value = 0;
	ft_bzero(&sa, sizeof(sa));
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
