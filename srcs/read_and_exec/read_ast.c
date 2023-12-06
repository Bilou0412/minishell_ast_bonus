/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:15:27 by soutin            #+#    #+#             */
/*   Updated: 2023/12/06 18:15:38 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	or_(t_vars *vars, t_ast *curr, bool is_pipe)
{
	if (read_ast(vars, curr->left, false))
		return (1);
	if (!vars->last_return_val)
		return (0);
	if (read_ast(vars, curr->right, false))
		return (1);
	return (0);
}

int	and_(t_vars *vars, t_ast *curr, bool is_pipe)
{
	if (read_ast(vars, curr->left, false))
		return (1);
	if (vars->last_return_val)
		return (0);
	if (read_ast(vars, curr->right, false))
		return (1);
	return (0);
}

int	pipex(t_vars *vars, t_ast *curr, bool is_pipe)
{
	if (read_ast(vars, curr->left, true))
		return (1);
	if (read_ast(vars, curr->right, true))
		return (1);
	// if (waitchilds(vars, , ) < 0)
	// 	return (-1);
	// if (close(vars->pipe_fd[0]) < 0)
	// 			exit_prog();
	return (0);
}

int	read_ast(t_vars *vars, t_ast *curr, bool is_pipe)
{
	if (!curr)
		return (0);
	// if ((curr->tokens->type > 3 && curr->tokens->type < 7)
	// 	&& (!curr->right || !curr->left))
	// 		return (1);
	if (curr->type == AND && and_(vars, curr, is_pipe))
		return (1);
	else if (curr->type == OR && or_(vars, curr, is_pipe))
		return (1);
	else if (curr->type == PIPE && pipex(vars, curr, is_pipe))
		return (1);
	else
	{
		if (exec_cmds(vars, &curr->tokens, is_pipe) < 0)
			return (1);
	}
	return (0);
}
