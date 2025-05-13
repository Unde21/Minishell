#include "exec.h"
#include "parsing.h"

void	heredoc(char *limiter)
{
	int		fd_heredoc;
	char	*heredoc;
	char	*line;

	line = NULL;
	heredoc = malloc(sizeof(char) * 26);
	if (!heredoc)
		if (print_err(ERR_MALLOC) == false)
			return ;
	heredoc = get_random_name(heredoc);
	fd_heredoc = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_heredoc == -1)
		if (print_err("ERROR : openning HEREDOC !\n") == false)
		{
			unlink(heredoc);
			return (free(heredoc));
		}
	while (1)
	{
		line = readline("> ");
		write(fd_heredoc, line, ft_strlen(line));
		write(fd_heredoc, "\n", 1);
		if (ft_strcmp(line, limiter) == 0)
			break ;
		free(line);
	}
	unlink(heredoc);
	free(heredoc);
	free(line);
	close(fd_heredoc);
}
