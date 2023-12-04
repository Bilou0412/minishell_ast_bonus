/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:07:50 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/04 22:18:59 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(char **arg_cmd, t_env **envl)
{
	t_env	*to_unset;
	t_env	*tmp;
	int		i;
	int		nb_cmd;

	i = 1;
	tmp = *envl;
	nb_cmd = ft_arraylen(arg_cmd);
	if (nb_cmd < 2)
		return (0);
	else
	{
		while (i < nb_cmd)
		{
			to_unset = search_envl(envl, arg_cmd[i]);
			if (!to_unset)
				return (0);
			while (tmp)
			{
				if (tmp->next && tmp->next == to_unset)
					tmp->next = to_unset->next;
				tmp = tmp->next;
			}
			i++;
		}
	}
	return (0);
}
