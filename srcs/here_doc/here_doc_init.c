
#include "exec.h"

char	*fill_heredoc(int fd_heredoc, char *limiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		if (need_expand(line))
		{
			
		}
		write(fd_heredoc, line, ft_strlen(line));
		write(fd_heredoc, "\n", 1);
		free(line);
	}
	close(fd_heredoc);
	return (NULL);
}

char	*heredoc(char *limiter)
{
	int		fd_heredoc;
	char	*filename;

	filename = NULL;
	filename = get_random_name(filename);
	if (!filename)
	{
		print_err("ERROR: heredoc creation failed !\n");
		return (NULL);
	}
	fd_heredoc = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_heredoc == -1)
	{
		print_err("ERROR : opening HEREDOC!\n");
		free(filename);
		return (NULL);
	}
	fill_heredoc(fd_heredoc, limiter);
	return (filename);
}
