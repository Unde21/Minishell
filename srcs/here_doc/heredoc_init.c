#include "exec.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

bool	expand_and_replace(t_data *data, char **line_ptr, char *limiter,
		char *line)
{
	if (is_expand_here_doc(limiter, line))
	{
		if (!replace_file_name(data, &line, HEREDOC, data->cmd->redir))
		{
			data->return_value = 1;
			*line_ptr = NULL;
			return (false);
		}
		*line_ptr = line;
	}
	return (true);
}

bool	fill_heredoc_loop(char **line_ptr, char *limiter, t_data *data)
{
	char	*line;
	char	*dup;

	line = *line_ptr;
	if (!line && g_return_value == 0)
	{
		data->return_value = 0;
		ft_printf(WARNING_HEREDOC);
		ft_printf("`%s')\n", limiter);
		return (false);
	}
	dup = remove_quote_heredoc(data, limiter);
	if (dup == NULL)
	{
		data->return_value = 1;
		return (print_err_null(ERR_MALLOC));
	}
	if (!ft_strcmp(line, dup))
	{
		free(dup);
		return (false);
	}
	free(dup);
	return (expand_and_replace(data, line_ptr, limiter, line));
}

char	*fill_heredoc(t_data *data, int fd_heredoc, char *limiter)
{
	char	*line;
	char	*old_line;

	old_line = NULL;
	while (1)
	{
		if (data->return_value != 0)
		{
			close(fd_heredoc);
			return (NULL);
		}
		line = readline(PROMPT_HERE_DOC);
		if (g_return_value == 130)
		{
			data->return_value = 130;
			break ;
		}
		if (fill_heredoc_loop(&line, limiter, data) == false)
			break ;
		ft_dprintf(fd_heredoc, "%s\n", line);
		free(line);
	}
	free(line);
	close(fd_heredoc);
	return (NULL);
}

char	*heredoc(t_data *data, t_redir *redir, char *limiter)
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
		free(filename);
		return (print_err_null(ERR_OP_FD));
	}
	fill_heredoc(data, fd_heredoc, limiter);
	free(redir->file);
	return (filename);
}
