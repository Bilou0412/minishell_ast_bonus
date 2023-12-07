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

int	close_pipe(t_vars *vars, t_ast *curr, bool left)
{
	if (left)
	{
		if (curr->left && curr->left->type == PIPEN)
			if (close(vars->pipe_fd[0]) < 0)
				return (-1);
	}
	else if (curr->right && curr->right->type == PIPEN)
		if (close(vars->pipe_fd[0]) < 0)
			return (-1);
	return (0);
}

int	or_(t_vars *vars, t_ast *curr, bool is_pipe)
{
	if (read_ast(vars, curr->left, false))
		return (1);
	close_pipe(vars, curr, LEFT);
	if (!vars->last_return_val)
		return (0);
	if (read_ast(vars, curr->right, false))
		return (1);
	close_pipe(vars, curr, RIGHT);
	return (0);
}

int	and_(t_vars *vars, t_ast *curr, bool is_pipe)
{
	if (read_ast(vars, curr->left, false))
		return (1);
	close_pipe(vars, curr, LEFT);
	if (vars->last_return_val)
		return (0);
	if (read_ast(vars, curr->right, false))
		return (1);
	close_pipe(vars, curr, RIGHT);
	return (0);
}

int	pipex(t_vars *vars, t_ast *curr, bool is_pipe)
{
	if (pipe(vars->pipe_fd) < 0)
		return (1);
	if (read_ast(vars, curr->left, true))
		return (1);
	if (read_ast(vars, curr->right, true))
		return (1);
	if (close(vars->pipe_fd[0]) < 0)
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
	if (curr->type == ANDN && and_(vars, curr, is_pipe))
		return (1);
	else if (curr->type == ORN && or_(vars, curr, is_pipe))
		return (1);
	else if (curr->type == PIPEN && pipex(vars, curr, is_pipe))
		return (1);
	else if (curr->type == CMDN)
	{
		if (exec_cmds(vars, &curr->tokens, is_pipe) < 0)
			return (1);
	}
	return (0);
}
