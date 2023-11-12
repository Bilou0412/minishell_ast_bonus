/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:14:40 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/12 10:08:44 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(t_vars *vars, t_tokens **head)
{
	t_tokens *current;

	current = *head;
	if (!ft_strncmp(current->string, "cd", 3))
	{
		if(cd(head,vars->envl) < 0)
			vars->last_return_val = 1;
		return (1);
	}
	return (0);
}