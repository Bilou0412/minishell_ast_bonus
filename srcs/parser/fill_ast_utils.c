/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ast_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:20:03 by soutin            #+#    #+#             */
/*   Updated: 2023/12/03 20:56:42 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_last_leaf(t_tokens *current)
{
	t_tokens	*tmp;

	tmp = current;
	while (tmp->next && (tmp->next->type < PIPE || tmp->next->type > AND))
		tmp = tmp->next;
	if (tmp->type == O_PARENTHESIS)
		return (1);
	if (!tmp->next)
		return (1);
	return (0);
}

void	ft_newleaf(t_ast **node, t_tokens **current)
{
	t_tokens	*tmp;

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
	}
	else if (*current)
	{
		tmp = (*current)->next;
		(*current)->next = NULL;
		ft_tokadd_front(&(*node)->tokens, *current);
		*current = tmp;
	}
}
