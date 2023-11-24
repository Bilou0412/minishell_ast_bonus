/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:13:52 by soutin            #+#    #+#             */
/*   Updated: 2023/11/22 16:21:10 by soutin           ###   ########.fr       */
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

int	tough_choices(t_vars *vars, int i, int nb_cmds)
{
	if (vars->cmd.infiles)
	{
		if (multiple_dup2(vars, 1, 0) < 0)
			return (freevars(vars, 1), -1);
	}
	else if (i != 0 && vars->cmd.nb_pipes > 1)
	{
		if (dup2(vars->tmp_fd, STDIN_FILENO) < 0)
			return (freevars(vars, 1), -1);
		if (close(vars->tmp_fd) < 0)
			return (freevars(vars, 1), -1);
	}
	if (vars->cmd.outfiles)
	{
		if (multiple_dup2(vars, 0, 0) < 0)
			return (freevars(vars, 1), -1);
	}
	else if (i != vars->cmd.nb_pipes && vars->cmd.nb_pipes > 1)
		if (dup2(vars->pipe_fd[1], STDOUT_FILENO) < 0)
			return (freevars(vars, 1), -1);
	return (0);
}

int	redirections(t_vars *vars)
{
	if (vars->cmd.infiles)
	{
		if (multiple_dup2(vars, 1, 0) < 0)
			return (-1);
	}
	else if (vars->cmd.outfiles)
	{
		if (multiple_dup2(vars, 0, 0) < 0)
			return (-1);
	}
	return (0);
}

void	in_out_pipe(t_vars *vars, t_tokens **head, int i)
{
	
	if (init_cmd_and_files(vars, head) < 0)
		exit(1);
	if (tough_choices(vars, i, vars->cmd.nb_pipes + 1) < 0)
		exit(1);
	ft_putnbr_fd(vars->cmd.nb_pipes, 2);	
	if (vars->cmd.nb_pipes )
	{
		if (close(vars->pipe_fd[1]) < 0 || close(vars->pipe_fd[0]) < 0)
		{
			freevars(vars, 1);
			exit(1);
		}
		
	}
	if (is_builtin_pipe(vars, head))
	{
		freevars(vars, 1);
		exit(0);
	}
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

int	exec_pipeline(t_vars *vars, t_tokens **head)
{
	int			i;
	int			pid[1024];
	t_tokens	*tmp;
	t_tokens	*tmp2;
	t_tokens	*initial_head;

	i = 0;
	initial_head = *head;
	while (i < vars->cmd.nb_pipes + 1)
	{
		tmp = *head;
		tmp2 = *head;
		while (tmp->next && tmp->next->type != PIPE)
			tmp = tmp->next;
		if (tmp->next && tmp->next->type == PIPE)
		{
			*head = tmp->next->next;
			free(tmp->next->string);
			free(tmp->next);
			tmp->next = NULL;
		}
		if (vars->cmd.nb_pipes)
			if (pipe(vars->pipe_fd) < 0)
				return (perror("pipe"), -1);
		pid[i] = fork();
		if (pid[i] < 0)
			return (perror("Fork"), -1);
		if (!pid[i])
		{
			in_out_pipe(vars, &tmp2, i);
		}
		if (vars->cmd.nb_pipes)
		{
			if (close(vars->pipe_fd[1]) < 0)
				return (-1);
			if (i != 0)
				close(vars->tmp_fd);
			vars->tmp_fd = vars->pipe_fd[0];
		}
		if (i < vars->cmd.nb_pipes)
			tmp->next = *head;
		i++;
	}
	if (waitchilds(vars, pid, i) < 0)
		return (-1);
	*head = initial_head;
	if (vars->cmd.nb_pipes)
		close(vars->pipe_fd[0]);
	return (0);
}

int	exec_cmd(t_vars *vars, t_tokens **head)
{
	if (!is_builtin_simple(vars, head))
	{
		vars->pid[vars->nb_forks] = fork();
		if (vars->pid[vars->nb_forks] < 0)
			return (perror("Fork"), -1);
		if (!vars->pid[vars->nb_forks])
		{
			if (init_cmd_and_files(vars, head) < 0)
				exit(1);
			if (redirections(vars) < 0)
				exit(1);
			freevars(vars, 0);
			if (execve(vars->cmd.path, vars->cmd.argv, vars->envp) < 0)
			{
				freevars(vars, 1);
				exit(1);
			}
		}
		vars->nb_forks++;
	}
	return (0);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_vars	vars;

// 	if (ac >= 5 && ac <= 1027)
// 	{
// 		if (init_vars(&vars, ac, av, envp) < 0)
// 			return (1);
// 		if (exec_pipeline(&vars) < 0)
// 			return (1);
// 		freetabs(vars.envp_paths);
// 		if (vars.limiter)
// 			unlink("here_doc");
// 		close(vars.pipe_fd[0]);
// 	}
// 	else
// 		ft_printf("parse error near `|\' ");
// 	return (0);
// }
