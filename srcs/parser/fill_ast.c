/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:44:33 by soutin            #+#    #+#             */
/*   Updated: 2023/12/03 21:07:49 by soutin           ###   ########.fr       */
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
		is_leaf(current, node);
	}
	return (0);
}

int	leaf_position(t_tokens **curr_tok, t_ast **curr_node)
{
	if (((*curr_tok)->type >= PIPE && (*curr_tok)->type <= AND)
		&& (*curr_tok)->type != C_PARENTHESIS)
		return (0);
	if (is_last_leaf(*curr_tok))
	{
		is_leaf(curr_tok, (*curr_node));
		return (1);
	}
	else
	{
		ft_newleaf(&(*curr_node)->right, NULL);
		is_leaf(curr_tok, (*curr_node)->right);
	}
	return (0);
}

int	is_last_pipe(t_tokens *curr)
{
	t_tokens *tmp;
	int		flag;

	tmp = curr->next;
	while (tmp && (tmp->type < PIPE || tmp->type > AND))
	{
		if (tmp->type == C_PARENTHESIS)
		{
			flag = 1;
			tmp = tmp->next;
			while (tmp && flag)
			{
				if (tmp->type == C_PARENTHESIS)
					flag++;
				else if (tmp->type == O_PARENTHESIS)
					flag--;
				tmp = tmp->next;
			}
		}
		else
			tmp = tmp->next;
	}
	if (tmp && tmp->type == PIPE)
		return (0);
	return (1);
}

int	parent_is_pipe(t_ast *curr, t_ast *to_find)
{
	if (!curr)
		return (0);
	if (parent_is_pipe(curr->left, to_find))
		return (1);
	if (parent_is_pipe(curr->right, to_find))
		return (1);
	// if ((curr->left == to_find || curr->right == to_find) && curr == _vars()->ast)
	// 	return (1);
	if ((curr->right == to_find || curr->left == to_find)
		&& ((!curr->tokens && curr == _vars()->ast)
		|| (curr->tokens && curr->tokens->type == PIPE)))
		return (1);
	return (0);
}

int	new_branch(t_tokens **curr_tok, t_ast **curr_node)
{
	if (!*curr_tok)
		return (0);
	if ((*curr_tok)->type == PIPE && is_last_pipe(*curr_tok))
	{
		(*curr_node)->tokens = *curr_tok;
		*curr_tok = (*curr_tok)->next;
		(*curr_node)->tokens->next = NULL;
		ft_newleaf(&(*curr_node)->left, NULL);
		is_leaf(curr_tok, (*curr_node)->left);
		return (0);
	}
	(*curr_node)->tokens = *curr_tok;
	*curr_tok = (*curr_tok)->next;
	(*curr_node)->tokens->next = NULL;
	is_branch(curr_tok, &(*curr_node)->left);
	return (0);
}

 // echo 1 | echo 2 || echo 3 | (echo 4 || echo 5 && echo 6 | echo 10) | echo 7 | echo 8 | echo 9

t_tokens	*next_token_is_pipe(t_tokens **curr_tok)
{
	t_tokens	*tmp;
	int			flag;

	// if (i && (*curr_tok)->type != AND && (*curr_tok)->type != OR)
	// 	return (0);
	tmp = (*curr_tok);
	while (tmp && (tmp->type < PIPE || tmp->type > AND))
	{
		if (tmp->type == C_PARENTHESIS)
		{
			flag = 1;
			tmp = tmp->next;
			while (tmp && flag)
			{
				if (tmp->type == C_PARENTHESIS)
					flag++;
				else if (tmp->type == O_PARENTHESIS)
					flag--;
				tmp = tmp->next;
			}
		}
		else if (tmp->type == O_PARENTHESIS)
			return (NULL);		
		else
			tmp = tmp->next;
	}
	if (tmp && tmp->type == PIPE)
		return (tmp);
	return (NULL);
}

int	branch_position(t_tokens **curr_tok, t_ast **curr_node)
{
	t_tokens	*tmp;
	
	printf("%p %p\n", _vars()->ast, *curr_node);
	if ((*curr_tok)->type == C_PARENTHESIS)
	{
		tmp = *curr_tok;
		*curr_tok = (*curr_tok)->next;
		ft_collector(tmp->string, true);
		ft_collector(tmp, true);
		is_branch(curr_tok, &(*curr_node)->right);
	}
	// else if ((*curr_tok)->type == PIPE && find_parent(_vars()->ast, *curr_node)->tokens->type != PIPE)
	// {
	// 	is_branch(curr_tok, &(*curr_node)->right, ++i);
	// }
	else if (next_token_is_pipe(curr_tok)
			&& (_vars()->ast == *curr_node
			|| !parent_is_pipe(_vars()->ast, *curr_node)))
	{
		if (leaf_position(curr_tok, &(*curr_node)->right))
		ft_newleaf(&(*curr_node)->right, NULL);
			return (1);
		(*curr_node)->tokens = *curr_tok;
		*curr_tok = (*curr_tok)->next;
		(*curr_node)->tokens->next = NULL;
		// ft_newleaf(&(*curr_node)->right, next_token_is_pipe(curr_tok));
		// new_branch(curr_tok, &(*curr_node)->right);
		is_branch(curr_tok, &(*curr_node)->right);
		// return (1);
	}
	return (0);
}

int	is_branch(t_tokens **curr_tok, t_ast **curr_node)
{
	if (!*curr_tok)
		return (0);
	ft_newleaf(curr_node, NULL);
	if (branch_position(curr_tok, curr_node))
		return (0);
	if (leaf_position(curr_tok, curr_node))
			return (0);
	
	new_branch(curr_tok, curr_node);
	return (0);
}

int	launch_ast(t_vars *vars)
{
	is_branch(&vars->tokens, &vars->ast);
	print_tree(vars->ast, 0);
	// tcsetattr(STDIN_FILENO, TCSANOW, &vars->original);
	// if (read_ast(vars, vars->ast))
	// 			return (-1);
	// if (waitchilds(vars, vars->pid, vars->nb_forks) < 0)
	// 		return (-1);
	freevars(vars, 0);
	return (0);
}
