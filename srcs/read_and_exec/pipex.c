/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:13:52 by soutin            #+#    #+#             */
/*   Updated: 2023/12/06 18:17:21 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirections(t_vars *vars)
{
	if (vars->cmd.infiles)
	{
		if (multiple_dup2(vars, 1, 0) < 0)
			exit_prog(1);
	}
	if (vars->cmd.outfiles)
	{
		if (multiple_dup2(vars, 0, 0) < 0)
			exit_prog(1);
	}
	return (0);
}

void	in_out_pipe(t_vars *vars, t_tokens **head)
{
	int	flag;

	if (init_cmd_and_files(vars, head) < 0)
		(ft_collector(NULL, true), exit(1));
	if (vars->cmd.argv && is_builtin(vars->cmd.argv[0]))
	{
		flag = exec_builtin(vars, head, 1);
		ft_collector(NULL, true);
		if (flag < 0)
			exit(1);
		exit(0);
	}
	freevars(vars, 0);
	if (execve(vars->cmd.path, vars->cmd.argv, vars->cmd.envp) < 0)
	{
		ft_collector(NULL, true);
		exit(1);
	}
}

int	count_pipes(t_tokens *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token->type == PIPE)
			i++;
		token = token->next;
	}
	return (i);
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
int	exec_simple(t_vars *vars, t_tokens **head)
{
	int	pid;

	pid = 0;
	if (is_builtin_simple(vars, head))
		return (0);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (!pid)
	{
		vars->cmd.envp = env_to_tab(&vars->envl);
		sort_cmd(vars, head);
		if (vars->cmd.argv)
			init_cmd_path(vars);
		redirections(vars);
		freevars(vars, 0);
		free_envl(&vars->envl);
		if (execve(vars->cmd.path, vars->cmd.argv, vars->cmd.envp) < 0)
			exit_prog(1);
	}
	else
		waitchilds(vars, &pid, 1);
	return (0);
}

int	exec_cmds(t_vars *vars, t_tokens **head, bool is_pipe)
{
	int			pid[2];

	if (!is_pipe)
		exec_simple(vars, head);
	else
	{
		pid[0] = fork();
		if (pid[0] < 0)
			return (perror("Fork"), -1);
		if (!pid[0])
			in_out_pipe(vars, head);
		if (close(vars->pipe_fd[1]) < 0)
			return (-1);
		if (close(vars->tmp_fd) < 0)
			return (-1);
		vars->tmp_fd = vars->pipe_fd[0];
		if (waitchilds(vars, pid, 2) < 0)
			return (-1);
	}
	return (0);
}
