/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:14:40 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/04 23:13:41 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	choose_the_one_2(t_vars *vars, t_tokens **head)
{
	if (!ft_strncmp((*head)->string, "pwd", 4))
	{
		if (pwd(vars->cmd.argv) < 0)
			return (-1);
	}
	else if (!ft_strncmp((*head)->string, "clear", 6))
		clear();
	else if (!ft_strncmp((*head)->string, "export", 7))
	{
		if (export(vars->cmd.argv, &vars->envl) < 0)
			return (-1);
	}
	else if (!ft_strncmp((*head)->string, "exit", 5))
		exit_prog();
	else if (!ft_strncmp((*head)->string, "unset", 6))
	{
		if (unset(vars->cmd.argv, &vars->envl) < 0)
			return (-1);
	}
	return (0);
}

int	choose_the_one(t_vars *vars, t_tokens **head)
{
	if (!ft_strncmp((*head)->string, "cd", 3))
	{
		if (cd(vars->cmd.argv, &vars->envl) < 0)
			return (-1);
	}
	else if (!ft_strncmp((*head)->string, "echo", 5))
	{
		if (echo(vars->cmd.argv) < 0)
			return (-1);
		return (0);
	}
	else if (!ft_strncmp((*head)->string, "env", 4))
		env(&vars->envl);
	else if (choose_the_one_2(vars, head) < 0)
		return (-1);
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
		if (sort_cmd(vars, head) < 0)
			exit_prog();
		if (vars->cmd.outfiles)
		{
			save = dup(1);
			if (!save || multiple_dup2(vars, 0, 1) < 0)
				exit_prog();
		}
	}
	if (choose_the_one(vars, head) < 0)
	{
		vars->last_return_val = 1;
		if (save)
			close(save);
		exit_prog();
	}
	if (vars->cmd.outfiles && !ispipe && (dup2(save, STDOUT_FILENO) < 0
			|| close(save) < 0))
		exit_prog();
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