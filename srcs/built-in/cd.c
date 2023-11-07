#include "../../inc/minishell.h"

char	*get_home(char **envl)
{
	int		i;
	char	*path_home;

	i = 0;
	path_home = NULL;
	while (envl[i] && !path_home)
	{
		if (ft_strncmp("HOME", envl[i], 4))
		{
			path_home = ft_substr(envl[i], 4, ft_strlen(envl[i]));
			if (!path_home)
				return (NULL);
		}
		i++;
	}
    return (path_home);
}
int	cd(char *path, char **envl)
{
	char *path_home;

	if (path)
	{
		if (chdir(path))
			return (-1);
	}
	else if (*path)
	{
		path_home = get_home(envl);
		if (!path_home)
			return (-1);
		if (chdir(path_home))
			return (-1);
	}
	return (-1);
}