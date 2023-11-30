/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:18:53 by soutin            #+#    #+#             */
/*   Updated: 2023/11/30 18:44:58 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*search_envl(t_vars *vars, char *var_name)
{
	int	i;
	int	size_name_envl;
	int	size_name_var;

	i = 0;
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
	return (ft_collector(ft_strdup(""), false));
}

int	setup_env(t_vars *vars, char **envp)
{
	vars->envl = ft_arraydup(envp);
	return (0);
}
