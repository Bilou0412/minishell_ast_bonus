/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:18:53 by soutin            #+#    #+#             */
/*   Updated: 2023/11/28 16:34:23 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*search_envl(t_vars *vars, char *var_name)
{
	int	i;
	int	size_name_envl;
	int	size_name_var;
	// char *str;

	i = 0;
	// str = ft_calloc(1, sizeof(char));
	// if (!str);
	// 	return (NULL);
	// *str = '\0';
	size_name_var = ft_strlen_to_char(var_name, '=');
	while (vars->envl[i])
	{
		size_name_envl = ft_strlen_to_char(vars->envl[i], '=');
		if (size_name_envl == size_name_var)
		{
			if (!ft_strncmp(var_name, vars->envl[i], size_name_envl))
				return (vars->envl[i]);
		}
		i++;
	}
	return (ft_strdup(""));
}

int	setup_env(t_vars *vars, char **envp)
{
	vars->envl = ft_arraydup(envp);
	if (!vars->envl)
		return (-1);
	return (0);
}
