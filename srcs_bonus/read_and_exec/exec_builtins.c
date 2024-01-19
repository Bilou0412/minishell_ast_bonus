/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:14:40 by bmoudach          #+#    #+#             */
/*   Updated: 2024/01/19 21:32:34 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_vars *vars)
{
	if (!ft_strncmp(vars->cmd.argv[0], "cd", 3))
		return (cd(vars->cmd.argv, &vars->envl));
	else if (!ft_strncmp(vars->cmd.argv[0], "echo", 5))
		return (echo(vars->cmd.argv));
	else if (!ft_strncmp(vars->cmd.argv[0], "env", 4))
		env(&vars->envl);
	if (!ft_strncmp(vars->cmd.argv[0], "pwd", 4))
		return (pwd(vars->cmd.argv));
	else if (!ft_strncmp(vars->cmd.argv[0], "export", 7))
		return (export(vars->cmd.argv, &vars->envl));
	else if (!ft_strncmp(vars->cmd.argv[0], "exit", 5))
		return (exit_builtin(vars->cmd.argv[1], ft_arraylen(vars->cmd.argv)));
	else if (!ft_strncmp(vars->cmd.argv[0], "unset", 6))
		return (unset(vars->cmd.argv, &vars->envl));
	return (0);
}

int	check_stds(int *stds)
{
	if (stds[0])
		if (dup2(stds[0], STDIN_FILENO) < 0 || close(stds[0]) < 0)
			return (-1);
	if (stds[1])
		if (dup2(stds[1], STDOUT_FILENO) < 0 || close(stds[1]) < 0)
			return (-1);
	return (0);
}

int	is_builtin(char *word)
{
	if (!ft_strncmp(word, "./minishell", 11))
	{
		signal(SIGINT, SIG_IGN);
		return (0);
	}
	if (!ft_strncmp(word, "cd", 3))
		return (1);
	if (!ft_strncmp(word, "echo", 5))
		return (1);
	if (!ft_strncmp(word, "env", 4))
		return (1);
	if (!ft_strncmp(word, "pwd", 4))
		return (1);
	if (!ft_strncmp(word, "export", 7))
		return (1);
	if (!ft_strncmp(word, "unset", 6))
		return (1);
	if (!ft_strncmp(word, "exit", 5))
		return (1);
	return (0);
}
