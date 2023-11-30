/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:07:50 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/30 15:04:51 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_tokens **head, t_vars *all)
{
	int		to_del;
	char	*var;

	var = get_next_word(head);
	to_del = search_envl_index(var, all);
	if (to_del > -1)
	{
		all->envl = ft_del_string_array(to_del, all->envl);
		if (!all->envl)
			return (-1);
	}
	return (0);
}
