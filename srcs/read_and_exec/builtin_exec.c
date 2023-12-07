/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:14:40 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/07 22:44:13 by soutin           ###   ########.fr       */
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
	return (0);
}

int	exec_builtin(t_vars *vars, t_tokens **head, bool ispipe)
{
	t_tokens	*current;
	int			save;

	current = *head;
	save = 0;
	if (!ispipe)
	{
		sort_cmd(vars, head);
		if (vars->cmd.outfiles)
		{
			save = dup(1);
			if (!save || multiple_dup2(vars, 0, 1) < 0)
				exit_prog(1);
		}
	}
	if (choose_the_one(vars, head))
	{
		vars->last_return_val = 1;
		if (save)
			close(save);
		exit_prog(1);
	}
	if (vars->cmd.outfiles && !ispipe && (dup2(save, STDOUT_FILENO) < 0
			|| close(save) < 0))
		exit_prog(1);
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