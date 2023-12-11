/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:07:50 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/11 17:08:51 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_loop(char **arg_cmd, t_env **envl, int nb_cmd)
{
	t_env	*to_unset;
	t_env	*tmp;
	int		i;

	i = 1;
	while (i < nb_cmd)
	{
		tmp = *envl;
		to_unset = search_envl(envl, arg_cmd[i]);
		i++;
		if (!to_unset)
			continue ;
		while (tmp)
		{
			if (tmp->next && tmp->next == to_unset)
			{
				tmp->next = to_unset->next;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

int	unset(char **arg_cmd, t_env **envl)
{
	int		nb_cmd;

	nb_cmd = ft_arraylen(arg_cmd);
	if (nb_cmd < 2)
		return (0);
	else
		unset_loop(arg_cmd, envl, nb_cmd);
	return (0);
}
