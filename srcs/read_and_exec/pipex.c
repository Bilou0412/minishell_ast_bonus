/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:13:52 by soutin            #+#    #+#             */
/*   Updated: 2023/12/07 22:27:27 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirections(t_vars *vars)
{
	if (vars->cmd.infiles)
	{
		if (multiple_dup2(vars, 1, 0) < 0)
			exit_prog(1);
		free_files(&vars->cmd.infiles);
	}
	if (vars->cmd.outfiles)
	{
		if (multiple_dup2(vars, 0, 0) < 0)
			exit_prog(1);
		free_files(&vars->cmd.outfiles);
	}
	return (0);
}

int	is_builtin_simple(t_vars *vars, t_tokens **head)
{
	t_tokens	*tmp;

	tmp = *head;
	while (tmp && tmp->type < 4)
	{
		if (tmp->type < 4 && (!tmp->next || tmp->next->type != WORD))
			return (-1);
		if (tmp->type < 4)
			tmp = tmp->next->next;
	}
	if (!tmp || tmp->type != WORD)
		return (0);
	if (is_builtin(tmp->string))
	{
		exec_builtin(vars, head, false);
		freevars(vars, 2);
		return (1);
				
	}
	return (0);
}
int	exec_simple(t_vars *vars, t_tokens **head, bool is_pipe)
{
	int	pid;

	pid = 0;
	if (!is_pipe && is_builtin_simple(vars, head))
		return (0);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (!pid)
	{
		vars->cmd.envp = env_to_tab(&vars->envl);
		sort_cmd(vars, head);
		init_cmd_path(vars);
		redirections(vars);
		free_tree(&vars->ast);
		free_envl(&vars->envl);
		if (execve(vars->cmd.path, vars->cmd.argv, vars->cmd.envp) < 0)
			exit_prog(1);
	}
	else
		waitchilds(vars, &pid, 1);
	return (0);
}

int	exec_pipes(t_vars *vars, t_ast *curr, int *pipe_fds, bool direction)
{
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
