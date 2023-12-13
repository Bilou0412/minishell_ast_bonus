/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:13:52 by soutin            #+#    #+#             */
/*   Updated: 2023/12/13 16:20:58 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_builtin(t_vars *vars, t_tokens **head, int *save_stds)
{
	if (sort_cmd(vars, head) < 0)
		return (-1);
	if (vars->cmd.infiles)
		save_stds[0] = dup(0);
	if (vars->cmd.outfiles)
		save_stds[1] = dup(1);
	redirections(vars);
	return (0);
}

int	is_builtin_simple(t_vars *vars, t_tokens **head)
{
	t_tokens	*tmp;
	int			save_stds[2];

	save_stds[0] = 0;
	save_stds[1] = 0;
	tmp = *head;
	while (tmp && tmp->type < 4)
	{
		if (tmp->type < 4)
			tmp = tmp->next->next;
	}
	if (!tmp || tmp->type != WORD || !is_builtin(tmp->string))
		return (0);
	if (init_builtin(vars, head, save_stds) < 0)
		vars->last_return_val = 1;
	else
		vars->last_return_val = exec_builtin(vars);
	vars->return_value = vars->last_return_val;
	freetabs(vars->cmd.argv);
	vars->cmd.argv = NULL;
	if (check_stds(save_stds) < 0)
		return (-1);
	return (1);
}

void	init_cmd(t_vars *vars, t_tokens **head)
{
	rl_clear_history();
	if (sort_cmd(vars, head) < 0)
		exit_prog(1);
	redirections(vars);
	if (!*vars->cmd.argv)
		exit_prog(1);
	if (is_builtin(vars->cmd.argv[0]))
	{
		if (exec_builtin(vars))
			exit_prog(1);
		else
			exit_prog(0);
	}
	init_cmd_path(vars);
	free_tree(&vars->ast);
	vars->cmd.envp = env_to_tab(&vars->envl);
	free_envl(&vars->envl);
}

int	exec_simple(t_vars *vars, t_tokens **head, bool is_pipe)
{
	int	pid;

	pid = 0;
	expand(vars, head);
	if (!is_pipe && is_builtin_simple(vars, head))
		return (0);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (!pid)
	{
		signal(SIGINT, &ctrl_c_child);
		init_cmd(vars, head);
		if (execve(vars->cmd.path, vars->cmd.argv, vars->cmd.envp) < 0)
			exit_prog(126);
	}
	else
		waitchilds(vars, &pid, 1);
	if (!access("here_doc", F_OK))
		unlink("here_doc");
	return (0);
}
