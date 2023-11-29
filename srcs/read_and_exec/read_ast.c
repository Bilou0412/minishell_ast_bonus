/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:15:27 by soutin            #+#    #+#             */
/*   Updated: 2023/11/29 15:22:06 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	or_(t_vars *vars, t_ast *curr)
{
	if (read_ast(vars, curr->left))
		return (1);
	if (!vars->last_return_val)
		return (0);
	if (read_ast(vars, curr->right))
		return (1);
	return (0);
}

int	and_(t_vars *vars, t_ast *curr)
{
	if (read_ast(vars, curr->left))
		return (1);
	if (vars->last_return_val)
		return (0);
	if (read_ast(vars, curr->right))
		return (1);
	return (0);
}

int	read_ast(t_vars *vars, t_ast *curr)
{
	if (!curr)
		return (0);
	if ((curr->tokens->type > 3 && curr->tokens->type < 7))
		if (!curr->right || !curr->left)
			return (1);
	if (curr->tokens->type == AND)
	{
		if (and_(vars, curr))
			return (1);
	}
	else if (curr->tokens->type == OR)
	{
		if (or_(vars, curr))
			return (1);
	}
	else if ((curr->tokens->type != 5 && curr->tokens->type != 6))
	{
		if (exec_pipeline(vars, &curr->tokens) < 0)
			return (1);
		if (vars->cmd.nb_pipes)
			if (close(vars->pipe_fd[0]) < 0)
				return (-1);
	}
	return (0);
}
