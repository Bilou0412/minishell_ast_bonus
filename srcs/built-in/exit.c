/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:56:49 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/30 21:02:44 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_prog(void)
{
	t_vars *vars;
	
	vars = _vars();
	if (waitchilds(vars, vars->pid, vars->nb_forks) < 0)
		return (-1);
	ft_collector(NULL, true);
	exit(0);
}
