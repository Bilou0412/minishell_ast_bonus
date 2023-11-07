#include "../../inc/minishell.h"

int	pwd(void)
{
	char *cwd;
	char buff[PATH_MAX + 1];

	cwd = getcwd(buff, PATH_MAX + 1);
	if (cwd != NULL)
		printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}