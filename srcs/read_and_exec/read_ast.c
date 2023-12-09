/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:15:27 by soutin            #+#    #+#             */
/*   Updated: 2023/12/09 19:38:15 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	or_(t_vars *vars, t_ast *curr)
{
	if (read_ast(vars, curr->left, false))
		return (1);
	if (!vars->last_return_val)
		return (0);
	if (read_ast(vars, curr->right, false))
		return (1);
	return (0);
}

int	and_(t_vars *vars, t_ast *curr)
{
	if (read_ast(vars, curr->left, false))
		return (1);
	if (vars->last_return_val)
		return (0);
	if (read_ast(vars, curr->right, false))
		return (1);
	return (0);
}

int	exec_pipes(t_vars *vars, t_ast *curr, int *pipe_fds, bool direction)
{
	signal(SIGINT, &ctrl_c_child);
	if (direction == LEFT)
	{
		close(pipe_fds[0]);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
	}
	else
	{
		close(pipe_fds[1]);
		dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
	}
	if (read_ast(vars, curr, true))
		return (1);
	ft_collector(NULL, true);
	exit(0);
}

int	pipe_(t_vars *vars, t_ast *curr)
{
	int	pipe_fds[2];
	int	pids[2];

	if (pipe(pipe_fds) < 0)
		return (1);
	pids[0] = fork();
	if (!pids[0])
		exec_pipes(vars, curr->left, pipe_fds, LEFT);
	else
	{
		pids[1] = fork();
		if (!pids[1])
			exec_pipes(vars, curr->right, pipe_fds, RIGHT);
		else
		{
			close(pipe_fds[0]);
			close(pipe_fds[1]);
			waitchilds(vars, pids, 2);
		}
	}
	return (0);
}

int	read_ast(t_vars *vars, t_ast *curr, bool is_pipe)
{
	if (!curr)
		return (0);
	if (curr->type == ANDN)
	{
		if (and_(vars, curr))
			return (1);
	}
	else if (curr->type == ORN)
	{
		if (or_(vars, curr))
			return (1);
	}
	else if (curr->type == PIPEN)
	{
		if (pipe_(vars, curr))
			return (1);
	}
	else
		exec_simple(vars, &curr->tokens, is_pipe);
	return (0);
}
