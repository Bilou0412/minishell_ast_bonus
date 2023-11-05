/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 19:15:27 by soutin            #+#    #+#             */
/*   Updated: 2023/11/05 20:13:51 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// Ca permet de detruire les 2 tokens de fichier actuels de la commande
// ex: < infile cat
// devient : cat

void	delete_file_tokens(t_tokens **head, t_tokens **curr)
{
	t_tokens	*tmp;

	if (*curr == *head)
	{
		*head = (*head)->next->next;
		free((*curr)->next->string);
		free((*curr)->next);
		free((*curr)->string);
		free(*curr);
		*curr = *head;
	}
	else
	{
		tmp = *head;
		while (tmp->next && tmp->next != *curr)
			tmp = tmp->next;
		tmp->next = (*curr)->next->next;
		free((*curr)->next->string);
		free((*curr)->next);
		free((*curr)->string);
		free(*curr);
		*curr = tmp->next;
	}
}

// T'as capté

int	file_add_back(t_files **head, int new_fd)
{
	t_files		*tmp;
	t_files		*new;

	new = ft_calloc(1, sizeof(t_files));
	if (!new)
		return (-1);
	new->fd = new_fd;
	new->next = NULL;
	if (head)
	{
		if (*head == NULL)
			*head = new;
		else
		{
			tmp = *head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
	return (0);
}

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

// t'as capté ca stp

int	fill_cmd_argv(t_vars *vars, t_tokens *tokens)
{
	t_tokens	*tmp;
	int			i;

	i = 0;
	vars->cmd.argv = ft_calloc(ft_lstsize(tokens) + 1, sizeof (char*));
	if (!vars->cmd.argv)
		return (-1);
	tmp = tokens;
	while (tmp)
	{
		vars->cmd.argv[i] = tokens->string;
		tmp = tmp->next;
		i++;
	}
	vars->cmd.argv[i] = NULL;
	return (0);
}

// ouvrir les fds des différents fichiers de la commande
// enlever tous les fichiers avec leurs chevrons de la liste de tokens
// prendre les tokens restants pour les convertir en argv

int	sort_cmd(t_vars *vars, t_tokens **head)
{
	t_tokens	*current;

	current = *head;
	while (current)
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

// lire l'ast en partant d'en bas à gauche

int	read_ast(t_vars *vars, t_ast *curr)
{
	if (!curr)
		return (0);
	if ((curr->tokens->type > 3 && curr->tokens->type < 7)) // si t'es sur | || ou && et qu'un enfant 
		if (!curr->right || !curr->left)					// est NULL, c'est qu'il y a un problème
			return (1);
	if (read_ast(vars, curr->left))
		return (1);
	if (read_ast(vars, curr->right))
		return (1);
	if ((curr->tokens->type < 4 || curr->tokens->type > 6))
		if (sort_cmd(vars, &curr->tokens) < 0)
			return (printf("\nprout\n"), 1);
	return (0);
}
