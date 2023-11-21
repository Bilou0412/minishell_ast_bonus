/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:56:49 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/21 20:54:48 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exit_prog(t_vars *vars)
{
	if (waitchilds(vars, vars->pid, vars->nb_forks) < 0)
		return (-1);
	freevars(vars, 2);
	freetabs(_vars()->envl);
	freetabs(_vars()->cmd.env_paths);
	exit(0);
}
