/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:44:33 by soutin            #+#    #+#             */
/*   Updated: 2023/11/30 16:27:28 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_leaf(t_tokens **current, t_ast *node)
{
	t_tokens	*tmp;

	if (!*current)
		return (0);
	if ((*current)->type >= 4 && (*current)->type <= 6)
		return (0);
	if ((*current)->type < 4 || (*current)->type > 6)
	{
		if ((*current)->next && (*current)->next->type == O_PARENTHESIS)
		{
			tmp = (*current)->next;
			(*current)->next = tmp->next;
			ft_collector(tmp->string, true);
			ft_collector(tmp, true);
		}
		ft_newleaf(&node, current);
		if (is_leaf(current, node) < 0)
			return (-1);
	}
	return (0);
}

int	leaf_position(t_tokens **curr_tok, t_ast **curr_node)
{
	if (is_last_leaf(*curr_tok))
	{
		if (is_leaf(curr_tok, (*curr_node)) < 0)
			return (-1);
		return (0);
	}
	else
	{
		ft_newleaf(&(*curr_node)->right, NULL);
		is_leaf(curr_tok, (*curr_node)->right);
	}
	return (1);
}

int	new_branch(t_tokens **curr_tok, t_ast **curr_node)
{
	t_tokens	*tmp;

	if ((*curr_tok)->type == C_PARENTHESIS)
	{
		tmp = *curr_tok;
		*curr_tok = (*curr_tok)->next;
		ft_collector(tmp->string, true);
		ft_collector(tmp, true);
		is_branch(curr_tok, &(*curr_node)->right);
	}
	if (*curr_tok)
	{
		(*curr_node)->tokens = *curr_tok;
		*curr_tok = (*curr_tok)->next;
		(*curr_node)->tokens->next = NULL;
		is_branch(curr_tok, &(*curr_node)->left);
	}
	return (0);
}

int	is_branch(t_tokens **curr_tok, t_ast **curr_node)
{
	if (!*curr_tok)
		return (0);
	ft_newleaf(curr_node, NULL);
	if (((*curr_tok)->type < 4 || (*curr_tok)->type > 6)
		&& (*curr_tok)->type != C_PARENTHESIS)
	{
		if (!leaf_position(curr_tok, curr_node))
			return (0);
	}
	new_branch(curr_tok, curr_node);
	return (0);
}

int	launch_ast(t_vars *vars)
{
	is_branch(&vars->tokens, &vars->ast);
	print_tree(vars->ast, 0);
	tcsetattr(STDIN_FILENO, TCSANOW, &vars->original);
	// printtokens(&vars->tokens);
	if (read_ast(vars, vars->ast))
				return (-1);
	if (waitchilds(vars, vars->pid, vars->nb_forks) < 0)
			return (-1);
	freevars(vars, 0);
	return (0);
}
