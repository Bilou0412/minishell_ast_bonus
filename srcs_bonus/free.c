/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:15:26 by bmoudach          #+#    #+#             */
/*   Updated: 2024/01/18 20:17:18 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tokclear(t_tokens **lst)
{
	t_tokens	*t;
	t_tokens	*buf;

	if (!*lst)
		return ;
	t = *lst;
	while (t)
	{
		buf = t->next;
		ft_collector(t->string, true);
		ft_collector(t, true);
		t = buf;
	}
	*lst = NULL;
}

void	free_tree(t_ast **ast)
{
	if (!*ast)
		return ;
	free_tree(&(*ast)->left);
	free_tree(&(*ast)->right);
	ft_tokclear(&(*ast)->tokens);
	ft_collector(*ast, true);
	*ast = NULL;
}

void	freetabs(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		ft_collector(tab[i], true);
		i++;
	}
	ft_collector(tab, true);
	tab = NULL;
}

void	free_envl(t_env **lst)
{
	t_env	*t;
	t_env	*buf;

	if (!*lst)
		return ;
	t = *lst;
	while (t)
	{
		buf = t->next;
		ft_collector(*(&t->key), true);
		if (*(&t->value))
			ft_collector(*(&t->value), true);
		ft_collector(*(&t), true);
		t = buf;
	}
	*lst = NULL;
}

void	free_files(t_files **lst)
{
	t_files	*t;
	t_files	*buf;

	if (!*lst)
		return ;
	t = *lst;
	while (t)
	{
		buf = t->next;
		ft_collector(*&t, true);
		t = buf;
	}
	*lst = NULL;
}
