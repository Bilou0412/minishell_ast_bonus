/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:20:03 by soutin            #+#    #+#             */
/*   Updated: 2023/11/30 16:11:54 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_last_leaf(t_tokens *current)
{
	t_tokens	*tmp;

	tmp = current;
	while (tmp->next && tmp->next->type != 5 && tmp->next->type != 6)
		tmp = tmp->next;
	if (tmp->type == O_PARENTHESIS)
		return (1);
	if (!tmp->next)
		return (1);
	return (0);
}

t_ast	*ft_newleaf(t_ast **node, t_tokens **current)
{
	t_tokens	*tmp;

	if (current)
		tmp = (*current)->next;
	if (!*node)
	{
		*node = (t_ast*)ft_collector(ft_calloc(1, sizeof(**node)), false);
		if (current)
		{
			(*node)->tokens = *current;
			(*node)->tokens->next = NULL;
		}
		else
			(*node)->tokens = NULL;
		(*node)->left = NULL;
		(*node)->right = NULL;
		return (*node);
	}
	(*current)->next = NULL;
	ft_tokadd_front(&(*node)->tokens, *current);
	*current = tmp;
	return (*node);
}
