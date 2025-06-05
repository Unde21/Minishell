#include "exec.h"

bool	is_access_ok(char *path, int *return_value, char **path_cmd)
{
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			*path_cmd = path;
			*return_value = 0;
			return (true);
		}
		*return_value = 126;
		return (false);
	}
	*return_value = 127;
	return (false);
}