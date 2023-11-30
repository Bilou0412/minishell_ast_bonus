/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:15:26 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/30 18:36:51 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_tokclear(t_tokens **lst, void (*del)(void *))
{
	t_tokens	*t;
	t_tokens	*buf;

	if (!*lst)
		return ;
	t = *lst;
	while (t)
	{
		buf = t->next;
		ft_tokdelone(t, del);
		t = buf;
	}
	*lst = NULL;
}

void	ft_tokdelone(t_tokens *lst, void (*del)(void *))
{
	int	i;

	i = 0;
	if (!lst)
		return ;
	(*del)(lst->string);
	lst->string = NULL;
	if (lst->expand)
	{
		ft_collector(lst->expand, true);
	}
	ft_collector(lst, true);
}

void	free_tree(t_ast **ast)
{
	if (!*ast)
		return ;
	free_tree(&(*ast)->left);
	free_tree(&(*ast)->right);
	ft_tokclear(&(*ast)->tokens, &free);
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
		ft_collector(t, true);
		t = buf;
	}
	*lst = NULL;
}
void	super_free(void **__ptr)
{
	if (*__ptr)
	{
		free(*__ptr);
		*__ptr = NULL;
	}	
}

void	freevars(t_vars *vars, int i)
{
	if (i != FREE_BUILTIN)
	{
		free_tree(&vars->ast);
		ft_tokclear(&vars->tokens, &free);
	}
	free_files(&vars->cmd.infiles);
	free_files(&vars->cmd.outfiles);
	if (i == FREE_BUILTIN || i == FREE_FULL)
	{
		freetabs(vars->cmd.argv);
		ft_collector(vars->cmd.path, true);
		if (i == FREE_FULL)
		{
			freetabs(vars->envl);
			rl_clear_history();
		}
	}
}
