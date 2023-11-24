/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:13:52 by soutin            #+#    #+#             */
/*   Updated: 2023/11/24 23:37:32 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	multiple_dup2(t_vars *vars, int flag, int builtin)
{
	t_files	*tmp;

	if (flag)
	{
		tmp = vars->cmd.infiles;
		while (tmp)
		{
			if (dup2(tmp->fd, STDIN_FILENO) < 0)
				return (-1);
			if (close(tmp->fd) < 0)
				return (-1);
			tmp = tmp->next;
		}
		free_files(&vars->cmd.infiles);
	}
	else
	{
		tmp = vars->cmd.outfiles;
		while (tmp)
		{
			if (dup2(tmp->fd, STDOUT_FILENO) < 0)
				return (-1);
			if (close(tmp->fd) < 0)
				return (-1);
			tmp = tmp->next;
		}
		free_files(&vars->cmd.outfiles);
	}
	return (0);
}

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
	else if (i != vars->cmd.nb_pipes && vars->cmd.nb_pipes)
		if (dup2(vars->pipe_fd[1], STDOUT_FILENO) < 0)
			return (-1);
	return (0);
}

void	in_out_pipe(t_vars *vars, t_tokens **head, int i)
{
	if (init_cmd_and_files(vars, head, i) < 0)
		exit(1);
	// if (is_builtin(vars, head))
	// {
	// 	exec_builtin(vars, head, 1);
	// 	freevars(vars, 1);
	// 	exit(0);
	// }
	freevars(vars, 0);
	if (execve(vars->cmd.path, vars->cmd.argv, vars->envp) < 0)
	{
		freevars(vars, 1);
		exit(1);
	}
}

int	waitchilds(t_vars *vars, int *pid, int childmax)
{
	int	i;
	int	status;

	i = 0;
	while (i < childmax)
	{
		if (waitpid(pid[i], &status, 0) < 0)
			return (-1);
		i++;
		vars->last_return_val = WEXITSTATUS(status);
	}
	return (0);
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

int	dup_toks(t_tokens **new_lst, t_tokens *current)
{
	char	*buff;
	t_tokens	*new_token;

	buff = ft_strdup(current->string);
	if (!buff)
		return (-1);	
	new_token = ft_lstnew(buff, current->type);
	if (!new_token)
		return (ft_lstclear(new_lst, &free), -1);
	ft_lstadd_back(new_lst, new_token);
	return (0);
}

t_tokens	*p(t_vars *vars, t_tokens **head, int current_cmd)
{
	t_tokens	*tmp;
	t_tokens	*new_lst;
	int			i;
	
	i = 0;
	tmp = *head;
	new_lst = NULL;
	while (i < current_cmd)
	{
		while (tmp && tmp->type != PIPE)
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
		i++;
	}
	while (tmp)
	{
		if (dup_toks(&new_lst, tmp) < 0)
			return (NULL);
		if (tmp->next && tmp->next->type == PIPE)
			break;
		tmp = tmp->next;
	}
	return (new_lst);
}

int	exec_pipeline(t_vars *vars, t_tokens **head)
{
	int			i;
	int			pid[1024];
	t_tokens	*new;

	i = 0;
	vars->cmd.nb_pipes = count_pipes(*head);
	while (i < vars->cmd.nb_pipes + 1)
	{
		new = p(vars, head, i);
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
	if (vars->cmd.nb_pipes)
		close(vars->pipe_fd[0]);
	return (0);
}

// int	exec_cmd(t_vars *vars, t_tokens **head)
// {
// 	if (!is_builtin_simple(vars, head))
// 	{
// 		vars->pid[vars->nb_forks] = fork();
// 		if (vars->pid[vars->nb_forks] < 0)
// 			return (perror("Fork"), -1);
// 		if (!vars->pid[vars->nb_forks])
// 		{
// 			if (init_cmd_and_files(vars, head) < 0)
// 				exit(1);
// 			if (redirections(vars) < 0)
// 				exit(1);
// 			freevars(vars, 0);
// 			if (execve(vars->cmd.path, vars->cmd.argv, vars->envp) < 0)
// 			{
// 				freevars(vars, 1);
// 				exit(1);
// 			}
// 		}
// 		vars->nb_forks++;
// 	}
// 	return (0);
// }
