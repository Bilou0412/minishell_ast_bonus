/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:13:52 by soutin            #+#    #+#             */
/*   Updated: 2023/11/29 17:01:06 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	tough_choices(t_vars *vars, int i)
{
	if (vars->cmd.infiles)
	{
		if (multiple_dup2(vars, 1, 0) < 0)
			return (-1);
	}
	else if (i != 0 && vars->cmd.nb_pipes)
	{
		if (dup2(vars->tmp_fd, STDIN_FILENO) < 0)
			return (-1);
		if (close(vars->tmp_fd) < 0)
			return (-1);
	}
	if (vars->cmd.outfiles)
	{
		if (multiple_dup2(vars, 0, 0) < 0)
			return (-1);
	}
	else if (i != vars->cmd.nb_pipes)
		if (dup2(vars->pipe_fd[1], STDOUT_FILENO) < 0)
			return (-1);
	return (0);
}

void	in_out_pipe(t_vars *vars, t_tokens **head, int i)
{
	int	flag;

	if (init_cmd_and_files(vars, head, i) < 0)
		exit(1);
	if (vars->cmd.argv && is_builtin(vars->cmd.argv[0]))
	{
		flag = exec_builtin(vars, head, 1);
		ft_lstclear(head, &free);
		freevars(vars, 1);
		if (flag < 0)
			exit(1);
		exit(0);
	}
	ft_lstclear(head, &free);
	freevars(vars, 0);
	if (execve(vars->cmd.path, vars->cmd.argv, vars->envp) < 0)
	{
		freevars(vars, 1);
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
	if (vars->cmd.nb_pipes)
		return (0);
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
		exec_builtin(vars, head, 0);
		freevars(vars, 2);
		return (1);
				
	}
	return (0);
}

// int	end_of_cmd(t_vars *vars, t_tokens **head, int i)
// {
	
// }

int	exec_pipeline(t_vars *vars, t_tokens **head)
{
	int			i;
	int			pid[1024];
	t_tokens	*new;

	i = 0;
	vars->cmd.nb_pipes = count_pipes(*head);
	if (browse_lst_and_expand(head, vars) < 0)
		return (-1);
	if (is_builtin_simple(vars, head))
		return (0);
	while (i < vars->cmd.nb_pipes + 1)
	{
		new = duplicate_current_cmd(vars, head, i);
		if (!new)
			return (-1);
		if (vars->cmd.nb_pipes)
			if (pipe(vars->pipe_fd) < 0)
				return (perror("pipe"), -1);
		pid[i] = fork();
		if (pid[i] < 0)
			return (perror("Fork"), -1);
		if (!pid[i])
			in_out_pipe(vars, &new, i);
		if (vars->cmd.nb_pipes)
		{
			if (close(vars->pipe_fd[1]) < 0)
				return (-1);
			if (i != 0)
				if (close(vars->tmp_fd) < 0)
					return (-1);
			vars->tmp_fd = vars->pipe_fd[0];
		}
		ft_lstclear(&new, &free);
		i++;
	}
	if (waitchilds(vars, pid, i) < 0)
		return (-1);
	// if (vars->cmd.nb_pipes)
	// 	close(vars->tmp_fd);
	return (0);
}
