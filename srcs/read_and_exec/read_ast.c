/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:15:27 by soutin            #+#    #+#             */
/*   Updated: 2023/11/21 19:26:15 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	handle_files_2(t_cmd *cmd, t_tokens *arm)
{
	int	fd;

	if (arm->type == GREAT)
	{
		fd = open(arm->next->string, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd < 0)
			return (-1);
		if (file_add_back(&cmd->outfiles, fd) < 0)
			return (-1);
	}
	else if (arm->type == DGREAT)
	{
		fd = open(arm->next->string, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd < 0)
			return (-1);
		if (file_add_back(&cmd->outfiles, fd) < 0)
			return (-1);
	}
	return (0);
}

int	handle_files(t_cmd *cmd, t_tokens *arm)
{
	int	fd;

	if (!arm->next || (arm->next->type != WORD && arm->next->type != DOLLARS))
		return (-1);
	if (arm->type == LESS)
	{
		fd = open(arm->next->string, O_RDONLY);
		if (fd < 0)
			return (-1);
		if (file_add_back(&cmd->infiles, fd) < 0)
			return (-1);
	}
	else if (arm->type == DLESS)
	{
		if (here_doc_loop(cmd, arm) < 0)
			return (-1);
		fd = open("here_doc", O_RDONLY);
		if (fd < 0)
			return (-1);
		if (file_add_back(&cmd->infiles, fd) < 0)
			return (-1);
	}
	else if (handle_files_2(cmd, arm) < 0)
		return (-1);
	return (0);
}

int	sort_cmd(t_vars *vars, t_tokens **head)
{
	t_tokens	*current;

	current = *head;
	while (current && current->type != PIPE)
	{
		if (current->type < 4)
		{
			if (handle_files(&vars->cmd, current) < 0)
				return (-1);
			delete_file_tokens(head, &current);
		}
		else
			current = current->next;
	}
	if (fill_cmd_argv(vars, *head) < 0)
		return (-1);
	return (0);
}

int	or_(t_vars *vars, t_ast *curr)
{
	if (read_ast(vars, curr->left))
		return (1);
	if (!vars->last_return_val)
		return (0);
	if (read_ast(vars, curr->right))
		return (1);
	return (0);
}

int	and_(t_vars *vars, t_ast *curr)
{
	if (read_ast(vars, curr->left))
		return (1);
	if (vars->last_return_val)
		return (0);
	if (read_ast(vars, curr->right))
		return (1);
	return (0);
}

int	read_ast(t_vars *vars, t_ast *curr)
{
	if (!curr)
		return (0);
	if ((curr->tokens->type > 3 && curr->tokens->type < 7))
		if (!curr->right || !curr->left)
			return (1);
	if (curr->tokens->type == AND)
	{
		if (and_(vars, curr))
			return (1);
	}
	else if (curr->tokens->type == OR)
	{
		if (or_(vars, curr))
			return (1);
	}
	else if ((curr->tokens->type != 5 && curr->tokens->type != 6))
	{
		vars->cmd.nb_pipes = count_pipes(curr->tokens);
		if (vars->cmd.nb_pipes)
		{
			if (exec_pipeline(vars, &curr->tokens) < 0)
				return (1);
		}
		else
		{
			if (exec_cmd(vars, &curr->tokens) < 0)
				return (1);
		}
	}
	return (0);
}
