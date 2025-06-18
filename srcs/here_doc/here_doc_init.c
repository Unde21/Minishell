#include "exec.h"
#include "parsing.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_random_name(char *here_doc)
{
	char	c;
	int		i;
	int		fd;

	i = 0;
	here_doc = malloc(sizeof(char) * 26);
	if (!here_doc)
		return (print_err_null(ERR_MALLOC));
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
	{
		free(here_doc);
		return (print_err_null(ERR_OP_FD));
	}
	while (i < 25)
	{
		read(fd, &c, 1);
		if (ft_isprint(c) && c != '/')
			here_doc[i++] = c;
	}
	here_doc[i] = '\0';
	close(fd);
	return (here_doc);
}

char	*get_limiter(t_cmd *cmd)
{
	while (cmd->redir != NULL)
	{
		if (cmd->redir->type == HERE_DOC)
			return (cmd->redir->file);
		cmd->redir = cmd->redir->next;
	}
	return (NULL);
}

bool	fill_heredoc_loop(char **line_ptr, char *limiter, t_data *data)
{
	char	*line;

	line = *line_ptr;
	if (!line && g_return_value == 0)
	{
		data->return_value = 0;
		ft_printf(WARNING_HEREDOC);
		ft_printf("`%s')\n", limiter);
		return (false);
	}
	if (!ft_strcmp(line, limiter))
		return (false);
	if (is_expand_here_doc(line))
	{
		if (!replace_file_name(data, &line, HEREDOC, data->cmd->redir))
		// ya probleme de leak sur l expand du here_doc
		{
			data->return_value = 1;
			*line_ptr = NULL;
			return (false);
		}
		*line_ptr = line;
	}
	return (true);
}

char	*fill_heredoc(t_data *data, int fd_heredoc, char *limiter)
{
	char	*line;
	char	*old_line;

	old_line = NULL;
	while (1)
	{
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
