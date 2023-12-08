/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:44:33 by soutin            #+#    #+#             */
/*   Updated: 2023/12/08 17:01:51 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*is_leaf(t_tokens **curr_tok)
{
	t_ast		*node;
	t_tokens	*tmp;

	node = ft_astnew(CMDN, NULL, NULL);
	while (*curr_tok && !is_ope((*curr_tok)->type)
		&& (*curr_tok)->type != C_PARENTHESIS
		&& (*curr_tok)->type != O_PARENTHESIS)
	{
		tmp = *curr_tok;
		*curr_tok = (*curr_tok)->next;
		tmp->next = NULL;
		ft_tokadd_back(&node->tokens, tmp);
	}
	return (node);
}

t_ast	*is_term(t_tokens **curr_tok)
{
	t_ast	*node;
	
	if (!*curr_tok || is_ope((*curr_tok)->type))
		return (print_syntax_error((*curr_tok)->string), NULL);
	if ((*curr_tok)->type == O_PARENTHESIS)
	{
		del_a_tok_and_move_forward(curr_tok);
		if (!*curr_tok)
			return (NULL);
		node = is_branch(curr_tok, 0);
		if (*curr_tok && (*curr_tok)->type == C_PARENTHESIS)
			del_a_tok_and_move_forward(curr_tok);
		else
			return (NULL);
	}
	else
		node = is_leaf(curr_tok);
	return (node);
}

int	print_syntax_error(char *string)
{
	return (printf("zebishell: syntax error near unexpected token `%s\'\n",
		string));
}

int	syntax_error(t_tokens **head)
{
	t_tokens	*tmp;

	tmp = *head;
	if (tmp && tmp->type >= PIPE && tmp->type <= AND)
		return (print_syntax_error(tmp->string));
	if (go_throught_paren(&tmp))
		return (1);
	while (tmp)
	{
		if (tmp->type < PIPE && !tmp->next)
			return (print_syntax_error("newline"));
		if (tmp->type < PIPE && tmp->next->type < 10)
			return (print_syntax_error(tmp->next->string));
		if (tmp->type >= PIPE && tmp->type <= AND && !tmp->next)
			return (print_syntax_error("newline"));
		if (tmp->type >= PIPE && tmp->type <= AND
			&& tmp->next->type >= PIPE && tmp->next->type <= AND)
			return (print_syntax_error(tmp->next->string));
		tmp = tmp->next;
	}
	return (0);
}


int	go_throught_paren(t_tokens **head)
{
	t_tokens	*tmp;
	int			flag;

	tmp = *head;
	while (tmp)
	{
		if (tmp->type == C_PARENTHESIS)
			return (print_syntax_error(tmp->string));
		if (tmp->type == O_PARENTHESIS)
		{
			flag = 1;
			tmp = tmp->next;
			while (tmp && flag)
			{
				if (tmp->type == O_PARENTHESIS)
					flag++;
				else if (tmp->type == C_PARENTHESIS)
					flag--;
				tmp = tmp->next;
			}
			if (flag)
				return (print_syntax_error("("));
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

t_ast	*is_branch(t_tokens **curr_tok, int min_prec)
{
	t_ast	*left;
	t_ast	*right;
	int		curr_prec;
	int		curr_ope;
	
	left = is_term(curr_tok);
	if (!left)
		return (NULL);
	if (*curr_tok && (*curr_tok)->type == O_PARENTHESIS)
		return (print_syntax_error((*curr_tok)->string), NULL);
	while (*curr_tok && is_ope((*curr_tok)->type)
			&& value_prec((*curr_tok)->type) >= min_prec)
	{
		curr_ope = (*curr_tok)->type;
		curr_prec = value_prec(curr_ope) + 1;
		del_a_tok_and_move_forward(curr_tok);
		right = is_branch(curr_tok, curr_prec);
		if (!right)
			break ;
		left = ft_astnew(curr_ope, left, right);
	}
	return (left);
}

int	launch_ast(t_vars *vars)
{
	if (syntax_error(&vars->tokens))
		return (ft_tokclear(&vars->tokens), 0);
	vars->ast = is_branch(&vars->tokens, 0);
	// print_tree(vars->ast, 0);
	// tcsetattr(STDIN_FILENO, TCSANOW, &vars->original);
	if (read_ast(vars, vars->ast, false))
				return (-1);
	free_tree(&vars->ast);
	return (0);
}
