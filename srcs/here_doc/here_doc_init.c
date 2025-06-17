#include "exec.h"
#include "parsing.h"
#include <signal.h>

char	*fill_heredoc(t_data *data, int fd_heredoc, char *limiter)
{
	char	*line;
	
	while (1)
	{
		line = readline(PROMPT_HERE_DOC); // secure readline
		if (g_return_value == 130)
		{
			free(line);
			data->return_value = 130;
			break ;
		}
		if (!line && g_return_value == 0) // Leak de fd dans ce cas la + leak de params
		{
			free(line);
			data->return_value = 0;
			ft_printf("> bash: warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", limiter);
			break ;
		}
		if (!line)
			break ;
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		if (is_expand_redir(line))
		{
			if (!replace_file_name(data, &line, HEREDOC, data->cmd->redir))
			{
				data->return_value = 1;
				free(line);
				break ;
			}
		}
		ft_dprintf(fd_heredoc, "%s\n", line);
		free(line);
	}
	close(fd_heredoc);
	return (NULL);
}

char	*heredoc(t_data *data, char *limiter)
{
	int		fd_heredoc;
	char	*filename;

	set_signal_action();
	filename = NULL;
	filename = get_random_name(filename);
	if (!filename)
		return (NULL);
	fd_heredoc = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_heredoc == -1)
	{
		print_err(ERR_OP_FD);
		free(filename);
		return (NULL);
	}
	fill_heredoc(data, fd_heredoc, limiter);
	return (filename);
}
