/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:13:52 by soutin            #+#    #+#             */
/*   Updated: 2023/11/05 19:42:44 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// int	tough_choices(t_vars *vars, int i)
// {
// 	if (i == 0)
// 	{
// 		if (dup2(vars->fdi, STDIN_FILENO) < 0)
// 			return (freevars(vars, i), -1);
// 		if (close(vars->fdi) < 0)
// 			return (freevars(vars, i), -1);
// 	}
// 	if (i != 0)
// 	{
// 		if (dup2(vars->tmp_fd, STDIN_FILENO) < 0)
// 			return (freevars(vars, i), -1);
// 		if (close(vars->tmp_fd) < 0)
// 			return (freevars(vars, i), -1);
// 	}
// 	if (i != vars->nb_cmds - 1)
// 		if (dup2(vars->pipe_fd[1], STDOUT_FILENO) < 0)
// 			return (freevars(vars, i), -1);
// 	if (i == vars->nb_cmds - 1 && vars->fdo != -2)
// 	{
// 		if (dup2(vars->fdo, STDOUT_FILENO) < 0)
// 			return (freevars(vars, i), -1);
// 		if (close(vars->fdo) < 0)
// 			return (freevars(vars, i), -1);
// 	}
// 	return (0);
// }

// void	in_out_pipe(t_vars *vars, int i)
// {
// 	if (init_cmd_and_files(vars, i) < 0)
// 		exit(1);
// 	if (tough_choices(vars, i) < 0)
// 		exit(1);
// 	if (close(vars->pipe_fd[1]) < 0 || close(vars->pipe_fd[0]) < 0)
// 	{
// 		freevars(vars, -1);
// 		exit(1);
// 	}
// 	if (execve(vars->cmd.cmd_path, vars->cmd.argv, vars->envp) < 0)
// 	{
// 		freevars(vars, i);
// 		exit(1);
// 	}
// }

// int	waitchilds(t_vars *vars)
// {
// 	int	i;
// 	int	status;

// 	i = 0;
// 	while (i < vars->nb_cmds)
// 	{
// 		if (waitpid(vars->pid[i], &status, 0) < 0)
// 			return (-1);
// 		i++;
// 	}
// 	return (0);
// }

// int	exec_cmd(t_vars *vars)
// {
// 	static int	i;

// 	if (pipe(vars->pipe_fd) < 0)
// 		return (perror("pipe"), -1);
// 	vars->pid[i] = fork();
// 	if (vars->pid[i] < 0)
// 		return (perror("Fork"), -1);
// 	if (!vars->pid[i])
// 		in_out_pipe(vars, i);
// 	if (close(vars->pipe_fd[1]) < 0)
// 		return (-1);
// 	if (i != 0)
// 		close(vars->tmp_fd);
// 	vars->tmp_fd = vars->pipe_fd[0];
// 		i++;
// 	if (waitchilds(vars) < 0)
// 		return (-1);
// 	close(vars->tmp_fd);
//     i++;
// 	return (0);
// }

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
