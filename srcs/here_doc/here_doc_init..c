#include "exec.h"

char	get_random_name(int fd, char *here_doc)
{
	char	*c;
	int		i;

	i = 0;
	c = NULL;
	here_doc = malloc(sizeof(char) * 11);
	if (!here_doc)
		return (NULL);
	while (i < 10)
	{
		here_doc[i] = read(fd, &c, 1);
		if (!ft_isprint(here_doc[i]))
			break ;
		i++;
	}
	here_doc[i] = '\0';
	return (here_doc);
}

bool	heredoc_init(t_data *data)
{
	int fd;
	char *here_doc;

	here_doc = NULL;
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
	{
		print_err("ERROR : FD HERE_DOC !\n");
		return (false);
	}
	here_doc = get_random_name(fd, here_doc);
	printf("%s\n", here_doc);
}