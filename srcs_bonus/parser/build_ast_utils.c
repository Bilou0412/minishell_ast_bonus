/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:20:03 by soutin            #+#    #+#             */
/*   Updated: 2023/12/05 15:53:14 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_ast	*ft_astnew(t_node_type type, t_ast *left, t_ast *right)
{
	t_ast	*new;

	new = (t_ast *)ft_collector(ft_calloc(1, sizeof(t_ast)), false);
	new->tokens = NULL;
	new->type = type;
	new->left = left;
	new->right = right;
	return (new);
}

bool	is_ope(int type)
{
	if (type >= PIPE && type <= AND)
		return (true);
	return (false);
}

int	value_prec(int type)
{
	if (type == OR || type == AND)
		return (0);
	return (1);
}

void	del_a_tok_and_move_forward(t_tokens **curr_tok)
{
	t_tokens	*tmp;

	tmp = *curr_tok;
	*curr_tok = (*curr_tok)->next;
	ft_collector(tmp->string, true);
	ft_collector(tmp, true);
}
