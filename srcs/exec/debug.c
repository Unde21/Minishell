#include "exec.h"

void	print_list(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (data->listed_env->next != NULL)
	{
		printf("# => %d\n", i++);
		printf("key => %s\n", data->listed_env->key);
		printf("value => %s\n", data->listed_env->value);
		printf("full_line => %s\n\n", data->listed_env->full_line);
		data->listed_env = data->listed_env->next;
	}
}
void	print_env(t_data *data)
{
	int i;

	i = -1;
	while (data->env[++i])
		printf("# = %d\nenv = %s\n\n", i, data->env[i]);
}