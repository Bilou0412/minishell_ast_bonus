/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:14:40 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/21 21:35:38 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin_simple(t_vars *vars, t_tokens **head)
{
	t_tokens	*current;
	int			save;

	current = *head;
	sort_cmd(vars, head);
	save = dup(1);
	if (vars->cmd.outfiles)
	{
		if (multiple_dup2(vars, 0, 1) < 0)
			return (-1);
	}
	if (!ft_strncmp(current->string, "cd", 3))
	{
		if (cd(&current->next, vars) < 0)
			vars->last_return_val = 1;
		if (vars->cmd.outfiles)
			dup2(save, STDOUT_FILENO);
		return (1);
	}
//	else if (!ft_strncmp(current->string, "echo", 5))
	//{
		//if (echo(head, vars->envl) < 0)
			//vars->last_return_val = 1;
		//return (1);
//	}
	else if (!ft_strncmp(current->string, "env", 4))
	{
		if (env(vars->envl) < 0)
			vars->last_return_val = 1;
		if (vars->cmd.outfiles)
			dup2(save, STDOUT_FILENO);
		return (1);
	}
	else if (!ft_strncmp(current->string, "pwd", 4))
	{
		if (pwd() < 0)
			vars->last_return_val = 1;
		// dup2(save, STDOUT_FILENO);
		// freevars(vars, 2);
		return (1);
	}
	else if (!ft_strncmp(current->string, "export", 7))
	{
		if (export(&current->next, vars) < 0)
			vars->last_return_val = 1;
		if (vars->cmd.outfiles)
			dup2(save, STDOUT_FILENO);
		freevars(vars, 2);
		return (1);
	}
	else if (!ft_strncmp(current->string, "unset", 6))
	{
		if (unset(&current->next, vars) < 0)
			vars->last_return_val = 1;
		if (vars->cmd.outfiles)
			dup2(save, STDOUT_FILENO);
		freevars(vars, 2);
		return (1);
	}
	else if (!ft_strncmp(current->string, "exit", 5))
	{
		if (exit_prog(vars) < 0)
			vars->last_return_val = 1;
		if (vars->cmd.outfiles)
			dup2(save, STDOUT_FILENO);
		freevars(vars, 2);
		return (1);
	}
	return (0);
}
int	is_builtin_pipe(t_vars *vars, t_tokens **head)
{
	t_tokens	*current;

	current = *head;
	
	if (!ft_strncmp(current->string, "cd", 3))
	{
		if (cd(&current->next, vars) < 0)
			vars->last_return_val = 1;
		return (1);
	}
//	else if (!ft_strncmp(current->string, "echo", 5))
	//{
		//if (echo(head, vars->envl) < 0)
			//vars->last_return_val = 1;
		//return (1);
//	}
	else if (!ft_strncmp(current->string, "env", 4))
	{
		if (env(vars->envl) < 0)
			vars->last_return_val = 1;
		return (1);
	}
	else if (!ft_strncmp(current->string, "pwd", 4))
	{
		if (pwd() < 0)
			vars->last_return_val = 1;
		return (1);
	}
	else if (!ft_strncmp(current->string, "export", 7))
	{
		if (export(&current->next, vars) < 0)
			vars->last_return_val = 1;
		return (1);
	}
	else if (!ft_strncmp(current->string, "unset", 6))
	{
		if (unset(&current->next, vars) < 0)
			vars->last_return_val = 1;
		return (1);
	}
	else if (!ft_strncmp(current->string, "exit", 5))
	{
		if (exit_prog(vars) < 0)
			vars->last_return_val = 1;
		return (1);
	}
	return (0);
}
int	is_builtin(t_vars *vars, t_tokens **head)
{
	t_tokens	*current;

	current = *head;
	
	if (!ft_strncmp(current->string, "cd", 3))
		return (1);
	else if (!ft_strncmp(current->string, "echo", 5))
		return (1);
	else if (!ft_strncmp(current->string, "env", 4))
		return (1);
	else if (!ft_strncmp(current->string, "pwd", 4))
		return (1);
	else if (!ft_strncmp(current->string, "export", 7))
		return (1);
	else if (!ft_strncmp(current->string, "unset", 6))
		return (1);
	else if (!ft_strncmp(current->string, "exit", 5))
		return (1);
	return (0);
}