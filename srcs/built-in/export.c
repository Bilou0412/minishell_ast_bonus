#include "../../inc/minishell.h"

char	*search_envl(char *var, t_vars *all)
{
	int	i;

	i = 0;
	while (all->envl[i] && ft_strncmp(var, all->envl[i], ft_strlen(var) - 1))
		i++;
	return (all->envl[i]);
}

int	export(char *var, t_vars *all)
{
	int size;
	char *to_change;

	if (ft_strchr(var, '='))
		return (-1);
	to_change = search_envl(var, all);
    if(to_change)
    {
        free(to_change);
        to_change = ft_strdup(var);
    }
    else
    {
        
    }
}