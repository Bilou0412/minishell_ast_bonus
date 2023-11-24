/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:14:40 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/24 22:53:54 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	choose_the_one_3(t_vars *vars, t_tokens **head, int save)
{
	
	if (!ft_strncmp((*head)->string, "pwd", 4))
	{
		if (pwd() < 0)
			return (-1);
		if (vars->cmd.outfiles && !vars->cmd.nb_pipes)
			if (dup2(save, STDOUT_FILENO) < 0)
				return (-1);
		return (0);
	}
	else if (!ft_strncmp((*head)->string, "exit", 5))
	{
		if (exit_prog(vars) < 0)
			return (-1);
		if (vars->cmd.outfiles && !vars->cmd.nb_pipes)
			if (dup2(save, STDOUT_FILENO) < 0)
				return (-1);
		return (0);
	}
	return (0);
}

int	choose_the_one_2(t_vars *vars, t_tokens **head, int save)
{
	if (!ft_strncmp((*head)->string, "export", 7))
	{
		if (export(&(*head)->next, vars) < 0)
			return (-1);
		if (vars->cmd.outfiles && !vars->cmd.nb_pipes)
			if (dup2(save, STDOUT_FILENO) < 0)
				return (-1);
		return (0);
	}
	else if (!ft_strncmp((*head)->string, "unset", 6))
	{
		if (unset(&(*head)->next, vars) < 0)
			return (-1);
		if (vars->cmd.outfiles && !vars->cmd.nb_pipes)
			if (dup2(save, STDOUT_FILENO) < 0)
				return (-1);
		return (0);
	}
	return (0);
}

int	choose_the_one(t_vars *vars, t_tokens **head, int save)
{
	
	if (!ft_strncmp((*head)->string, "cd", 3))
	{
		if (cd(&(*head)->next, vars) < 0)
			return (-1);
		if (vars->cmd.outfiles && !vars->cmd.nb_pipes)
			if (dup2(save, STDOUT_FILENO) < 0)
				return (-1);
		return (0);
	}
//	else if (!ft_strncmp((*head)->string, "echo", 5))
	//{
		//if (echo(head, vars->envl) < 0)
			//return (-1);
		// if (vars->cmd.outfiles && !vars->cmd.nb_pipes)
		// 	if (dup2(save, STDOUT_FILENO) < 0)
		// 		return (-1);
		//return (0);
//	}
	else if (!ft_strncmp((*head)->string, "env", 4))
	{
		if (env(vars->envl) < 0)
			return (-1);
		if (vars->cmd.outfiles && !vars->cmd.nb_pipes)
			if (dup2(save, STDOUT_FILENO) < 0)
				return (-1);
		return (0);
	}
	return (0);
}

int	exec_builtin(t_vars *vars, t_tokens **head, int ispipe)
{
	t_tokens	*current;
	int			save;

	current = *head;
	save = 0;
	if (!ispipe)
	{
		if (sort_cmd(vars, head) < 0)
			return (-1);
		save = dup(1);
		if (!save)
			return (-1);
		if (vars->cmd.outfiles)
		{
			if (multiple_dup2(vars, 0, 1) < 0)
				return (-1);
		}
	}
	if (choose_the_one(vars, head, save) < 0)
	{
		vars->last_return_val = 1;
		if (!ispipe)
			return (-1);
		else
			exit(1);
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