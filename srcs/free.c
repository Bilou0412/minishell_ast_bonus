/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:15:26 by bmoudach          #+#    #+#             */
/*   Updated: 2023/12/06 20:21:50 by soutin           ###   ########.fr       */
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
		ft_tokdelone(t);
		t = buf;
	}
	*lst = NULL;
}

void	ft_tokdelone(t_tokens *lst)
{
	if (!lst)
		return ;
	ft_collector(lst->string, true);
	if (lst->expand)
		ft_collector(lst->expand, true);
	ft_collector(lst, true);
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
		// printf("argv : %p\n", tab[i]);
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
		ft_tokclear(&vars->tokens);
	}
	free_files(&vars->cmd.infiles);
	free_files(&vars->cmd.outfiles);
	if (i == FREE_BUILTIN || i == FREE_FULL)
	{
		freetabs(vars->cmd.argv);
		if (i == FREE_FULL)
		{
			free_envl(&vars->envl);
			ft_collector(vars->cmd.path, true);
			ft_collector(vars->cmd.envp, true);
			rl_clear_history();
		}
	}
}
