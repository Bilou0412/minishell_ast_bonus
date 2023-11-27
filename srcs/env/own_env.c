/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 19:18:53 by soutin            #+#    #+#             */
/*   Updated: 2023/11/27 18:46:24 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*search_envl(t_vars *vars, char *var_name)
{
	int	i;
	int	size_name_envl;
	int	size_name_var;
	char *str;

	i = 0;
	str = malloc(sizeof(char));
	*str = '\0';
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
	return (str);
}

int	setup_env(t_vars *vars, char **envp)
{
	vars->envl = ft_arraydup(envp);
	if (!vars->envl)
		return (-1);
	vars->cmd.env_paths = init_paths(vars);
	if (!vars->cmd.env_paths)
		return (freetabs(vars->envl), -1);
	return (0);
}
