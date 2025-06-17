#include "parsing.h"
#include <stdlib.h>
#include <unistd.h>

void	get_prompt(t_data *data, char **prompt)
{
	char	*code;
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
	{
		*prompt = NULL;
		return ;
	}
	code = ft_itoa(data->return_value);
	if (code != NULL)
	{
		if (data->return_value != 0)
			*prompt = ft_strdup(RED CROSS);
		else
			*prompt = ft_strdup(GREEN CHECK);
		*prompt = ft_strjoin_and_free(*prompt, code);
		*prompt = ft_strjoin_and_free(*prompt, END_BLUE);
		*prompt = ft_strjoin_and_free(*prompt, path);
		*prompt = ft_strjoin_and_free(*prompt, END_COLOR);
	}
	free(path);
	free(code);
}
