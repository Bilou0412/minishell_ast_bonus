/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:13:52 by soutin            #+#    #+#             */
/*   Updated: 2023/12/06 15:32:00 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirections(t_vars *vars)
{
	if (vars->cmd.infiles)
	{
		if (multiple_dup2(vars, 1, 0) < 0)
			return (-1);
	}
	if (vars->cmd.outfiles)
	{
		if (multiple_dup2(vars, 0, 0) < 0)
			return (-1);
	}
	return (0);
}

void	in_out_pipe(t_vars *vars, t_tokens **head, int i)
{
	int	flag;

	if (init_cmd_and_files(vars, head, i) < 0)
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
	if (execve(vars->cmd.path, vars->cmd.argv, vars->envp) < 0)
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

	if (is_builtin)
	pid = fork();
	if (pid < 0)
		return (-1);
	if (!pid)
	{
		sort_cmd(vars, head);
		redirections(vars);
		execve(vars->cmd.path, vars->cmd.argv, vars->cmd.envp);
	}
		
}

int	exec_cmds(t_vars *vars, t_tokens **head, bool is_pipe)
{
	int			pid[2];

	vars->cmd.envp = env_to_tab(&vars->envl);
	// printtab(vars->envp);
	// printf("--------------------------------------------\n");
	// ft_change_string_array(1, "okkokokokokokok", vars->envp);
	// printtab(vars->envp);
	if (is_builtin_simple(vars, head))
		return (0);
	if (vars->cmd.nb_pipes)
		if (pipe(vars->pipe_fd) < 0)
			return (perror("pipe"), -1);
	pid[0] = fork();
	if (pid[0] < 0)
		return (perror("Fork"), -1);
	if (!pid[0])
		in_out_pipe(vars, head);
	if (vars->cmd.nb_pipes)
	{
		if (close(vars->pipe_fd[1]) < 0)
			return (-1);
		if (close(vars->tmp_fd) < 0)
			return (-1);
		vars->tmp_fd = vars->pipe_fd[0];
	}
	if (waitchilds(vars, pid, 2) < 0)
		return (-1);
	return (0);
}
