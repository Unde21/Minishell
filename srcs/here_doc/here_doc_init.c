#include "exec.h"

char	*get_random_name(char *here_doc)
{
	char	c;
	int		i;
	int		fd;

	i = 0;
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
	{
		print_err("ERROR : FD HERE_DOC !\n");
		free(here_doc);
		return (NULL);
	}
	while (i < 25)
	{
		read(fd, &c, 1);
		if (ft_isprint(c))
			here_doc[i++] = c;
	}
	here_doc[i] = '\0';
	close(fd);
	return (here_doc);
}

void	heredoc_init(t_data *data)
{
	char	*here_doc;

	here_doc = malloc(sizeof(char) * 26);
	if (!here_doc)
		print_err(ERR_MALLOC);
	here_doc = get_random_name(here_doc);
}
