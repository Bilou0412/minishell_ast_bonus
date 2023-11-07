#include "../../inc/minishell.h"

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