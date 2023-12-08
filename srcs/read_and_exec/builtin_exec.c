/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:14:40 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/08 18:06:03 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	choose_the_one_2(t_vars *vars, t_tokens **head)
{
	if (!ft_strncmp(vars->cmd.argv[0], "pwd", 4))
	{
		if (pwd(vars->cmd.argv))
			return (1);
	}
	else if (!ft_strncmp(vars->cmd.argv[0], "clear", 6))
		clear();
	else if (!ft_strncmp(vars->cmd.argv[0], "export", 7))
	{
		if (export(vars->cmd.argv, &vars->envl))
			return (1);
	}
	else if (!ft_strncmp(vars->cmd.argv[0], "exit", 5))
		exit_prog(0);
	else if (!ft_strncmp(vars->cmd.argv[0], "unset", 6))
	{
		if (unset(vars->cmd.argv, &vars->envl))
			return (1);
	}
	return (0);
}

int	choose_the_one(t_vars *vars, t_tokens **head)
{
	if (!ft_strncmp(vars->cmd.argv[0], "cd", 3))
	{
		if (cd(vars->cmd.argv, &vars->envl))
			return (1);
	}
	else if (!ft_strncmp(vars->cmd.argv[0], "echo", 5))
	{
		if (echo(vars->cmd.argv))
			return (1);
		return (0);
	}
	else if (!ft_strncmp(vars->cmd.argv[0], "env", 4))
		env(&vars->envl);
	else if (choose_the_one_2(vars, head))
		return (1);
	freetabs(vars->cmd.argv);
	vars->cmd.argv = NULL;
	return (0);
}

int	check_stds(int *stds)
{
	if (stds[0])
		if (dup2(stds[0], STDIN_FILENO) < 0 || close(stds[0]) < 0)
			return (-1);
	if (stds[1])
		if (dup2(stds[1], STDOUT_FILENO) < 0 || close(stds[1]) < 0)
	return (0);
}

int	exec_builtin(t_vars *vars, t_tokens **head, bool ispipe)
{
	int			save_stds[2];

	save_stds[0] = 0;
	save_stds[1] = 0;
	if (!ispipe)
	{
		sort_cmd(vars, head);
		if (vars->cmd.infiles)
			save_stds[0] = dup(0);
		if (vars->cmd.outfiles)
			save_stds[1] = dup(1);
		redirection(vars);
	}
	if (choose_the_one(vars, head))
	{
		vars->last_return_val = 1;
		if (check_stds(save_stds) < 0)
			return (-1);
		exit_prog(1);
	}
	if (check_stds(save_stds) < 0)
		return (-1);
	return (0);
}

int	is_builtin(char *word)
{
	if (!ft_strncmp(word, "cd", 3))
		return (1);
	else if (!ft_strncmp(word, "clear", 6))
		return (1);
	else if (!ft_strncmp(word, "echo", 5))
		return (1);
	else if (!ft_strncmp(word, "env", 4))
		return (1);
	else if (!ft_strncmp(word, "pwd", 4))
		return (1);
	else if (!ft_strncmp(word, "export", 7))
		return (1);
	else if (!ft_strncmp(word, "unset", 6))
		return (1);
	else if (!ft_strncmp(word, "exit", 5))
		return (1);
	return (0);
}