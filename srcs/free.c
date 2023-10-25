/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:15:26 by bmoudach          #+#    #+#             */
/*   Updated: 2023/10/25 16:02:34 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_lstclear(t_tokens **lst, void (*del)(void*))
{
	t_tokens	*t;
	t_tokens	*buf;

	if (!lst)
		return ;
	t = *lst;
	while (t)
	{
		buf = t->next;
		ft_lstdelone(t, del);
		t = buf;
	}
	*lst = NULL;
}

void	ft_lstdelone(t_tokens *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(*del)(lst->string);
	free(lst);
}

void	free_cmds(t_cmds **cmds)
{
	t_cmds	*tmp;
	t_cmds	*buf;

	tmp = *cmds;
	if (!cmds)
		return ;
	while (tmp)
	{
		buf = tmp->next;
		free(tmp);
		tmp = buf;
	}
	*cmds = NULL;
}

void	free_tree(t_ast **ast)
{
	if (!*ast)
		return ;
	free_tree(&(*ast)->left);
	free_tree(&(*ast)->right);
	free_cmds(&(*ast)->cmds);
}