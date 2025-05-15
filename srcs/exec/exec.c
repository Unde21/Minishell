#include "exec.h"
#include "parsing.h"

void	executable(t_data *data)
{
	(void)data;
}

void	exec_init(t_data *data)
{
	init_listed_env(data);
	while (data->cmd != NULL)
	{
		if (is_heredoc(data))
			heredoc(get_limiter(data));
		if (is_cmd(data))
			printf("executable\n");
		else
			print_err(ERR_CMD);
		if (is_pipe(data))
			printf("there_is_pipe\n");
		data->cmd = data->cmd->next;
	}
	free_listed_env(data);
}
