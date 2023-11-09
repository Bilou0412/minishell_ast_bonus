/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:15:27 by soutin            #+#    #+#             */
/*   Updated: 2023/11/09 18:03:27 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// c'est moche mais ca ouvre tous les types de chevrons
// avec les bonnes permissions tout ca tout ca
// les deux premières conditions sont pour protéger
// file_add_back() sert à remplir une liste chainée de fd, inputfiles et
// outputfiles comme on peut avoir plusieurs inputfiles et outputfiles par cmd
int	handle_files(t_cmd *cmd, t_tokens *arm)
{
	int	fd;

	if (!arm->next)
		return (-1);
	if (arm->next->type != WORD && arm->next->type != DOLLARS)
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
	else if (arm->type == GREAT)
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

// la boucle ouvre tous les fds de la commande et
// supprime les tokens OPERATOR + FILENAME de la liste
// les tokens restants sont convertis en argv
int	sort_cmd(t_vars *vars, t_tokens **head)
{
	t_tokens	*current;

	current = *head;
	while (current)
	{
		if (current->type < 4)
		{
			if (handle_files(&vars->cmd, current) < 0)
				return (vars->last_return_val = 1, -1);
			delete_file_tokens(head, &current);
		}
		else
			current = current->next;
	}
	if (fill_cmd_argv(vars, *head) < 0)
		return (vars->last_return_val = 1, -1);
	return (0);
}

int	pipex(t_vars *vars, t_ast *curr)
{
	if (read_ast(vars, curr->left))
		return (1);
	if (read_ast(vars, curr->right))
		return (1);
	return (0);
}

int	or_(t_vars *vars, t_ast *curr)
{
	if (read_ast(vars, curr->left))
		return (1);
	if (curr->left->tokens->type == PIPE)
		close(vars->pipe_fd[0]);
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
	if (curr->left->tokens->type == PIPE)
		close(vars->pipe_fd[0]);
	if (vars->last_return_val)
		return (0);
	if (read_ast(vars, curr->right))
		return (1);
	return (0);
}

// lire l'ast en partant d'en bas à gauche
// si t'es sur | || ou && et qu'un enfant
// est NULL, c'est qu'il y a un problème
int	read_ast(t_vars *vars, t_ast *curr)
{
	if (!curr)
		return (0);
	if ((curr->tokens->type > 3 && curr->tokens->type < 7))
		if (!curr->right || !curr->left)
			return (1);
	if (curr->tokens->type == PIPE)
	{
		if (pipex(vars, curr))
			return (1);
	}
	else if (curr->tokens->type == AND)
	{
		if (and_(vars, curr))
			return (1);
	}
	else if (curr->tokens->type == OR)
	{
		if (or_(vars, curr))
			return (1);
	}
	if ((curr->tokens->type < 4 || curr->tokens->type > 6))
		if (sort_cmd(vars, &curr->tokens) < 0)
			return (printf("\nprout\n"), 1);
	return (0);
}
