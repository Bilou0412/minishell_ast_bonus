/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:44:33 by soutin            #+#    #+#             */
/*   Updated: 2023/10/31 16:22:06 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	leaf_position(t_tokens **curr_tok, t_ast **curr_node)
{
	if (is_last_leaf(*curr_tok))
	{
		is_leaf(curr_tok, (*curr_node));
		return (0);
	}
	else
	{
		if (!ft_newleaf(&(*curr_node)->right, NULL))
			return (-1);
		is_leaf(curr_tok, (*curr_node)->right);
	}
	return (1);
}

int	new_branch(t_tokens **curr_tok, t_ast **curr_node)
{
	int	flag;

	(*curr_node)->tokens = *curr_tok;
	*curr_tok = (*curr_tok)->next;
	(*curr_node)->tokens->next = NULL;
	flag = is_branch(curr_tok, &(*curr_node)->left);
	if (flag < 0)
		return (-1);
	if (!flag)
		return (0);
	return (1);
}

int	is_leaf(t_tokens **current, t_ast *node)
{
	if (!*current)
		return (0);
	if ((*current)->type >= 4 && (*current)->type <= 6)
		return (0);
	if ((*current)->type < 4 || (*current)->type > 6)
	{
		if (!ft_newleaf(&node, current))
			return (-1);
		if (is_leaf(current, node) < 0)
			return (-1);
	}
	return (0);
}

int	is_branch(t_tokens **curr_tok, t_ast **curr_node)
{
	int	flag;

	if (!*curr_tok)
		return (0);
	if (!ft_newleaf(curr_node, NULL))
		return (-1);
	if ((*curr_tok)->type == C_PARENTHESIS)
	{
		*curr_tok = (*curr_tok)->next;
		if (is_branch(curr_tok, &(*curr_node)->right) < 0)
			return (-1);
	}
	else if ((*curr_tok)->type > 4 || (*curr_tok)->type > 6)
	{
		flag = leaf_position(curr_tok, curr_node);
		if (flag < 0)
			return (-1);
		if (!flag)
			return (0);
	}
	if (*curr_tok && ((*curr_tok)->type >= 4 && (*curr_tok)->type <= 6))
	{
		flag = new_branch(curr_tok, curr_node);
		if (flag < 0)
			return (-1);
		if (!flag)
			return (0);
	}
	return (1);
}

int	launch_ast(t_tokens *head, t_ast **root)
{
	t_tokens	*tmp;

	*root = NULL;
	tmp = head;
	if (is_branch(&tmp, root) < 0)
		return (-1);
	print_tree(*root, 0);
	return (0);
}
