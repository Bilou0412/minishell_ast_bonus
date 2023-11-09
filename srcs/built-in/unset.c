/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:07:50 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/09 18:38:51 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	search_envl(char *var, t_vars *all)
{
	int	i;
	int	size_name_envl;
	int	size_name_var;

	i = 0;
	size_name_var = ft_strlen(var);
	while (all->envl[i])
	{
		size_name_envl = ft_strlen_to_char(all->envl[i], '=');
		if (size_name_envl == size_name_var)
		{
			if (!ft_strncmp(var, all->envl[i], size_name_envl))
				return (i);
		}
		i++;
	}
	return (-1);
}

int	unset(char *var, t_vars *all)
{
	int	to_del;

	to_del = search_envl(var, all);
	if (to_del > -1)
	{
		all->envl = ft_del_string_array(to_del, all->envl);
		if (!all->envl)
			return (-1);
	}
	return (0);
}
