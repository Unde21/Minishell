#include "exec.h"
#include "parsing.h"

// char	*fill_heredoc(int fd_heredoc, char *heredoc, char *limiter)
// {
// 	char	*line;

// 	line = NULL;
// 	while (1)
// 	{
// 		line = readline("> ");
// 		write(fd_heredoc, line, ft_strlen(line));
// 		write(fd_heredoc, "\n", 1);
// 		if (ft_strcmp(line, limiter) == 0)
// 			break ;
// 		free(line);
// 	}
// 	while (i < 25)
// 	{
// 		read(fd, &c, 1);
// 		if (ft_isprint(c) && c != '/')
// 			here_doc[i++] = c;
// 	}
// 	here_doc[i] = '\0';
// 	close(fd);
// 	return (here_doc);
// }

// char	*heredoc(char *limiter)
// {
// 	int		fd_heredoc;
// 	char	*heredoc;

// 	heredoc = malloc(sizeof(char) * 26);
// 	if (!heredoc)
// 		if (print_err(ERR_MALLOC) == false)
// 			return (NULL);
// 	heredoc = get_random_name(heredoc);
// 	fd_heredoc = open(heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (fd_heredoc == -1)
// 		if (print_err("ERROR : openning HEREDOC !\n") == false)
// 		{
// 			unlink(heredoc);
// 			free(heredoc);
// 			return (NULL);
// 		}
// 	fill_heredoc(fd_heredoc, heredoc, limiter);
// 	return (heredoc);
// }
