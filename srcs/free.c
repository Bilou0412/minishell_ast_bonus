/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:15:26 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/27 16:04:46 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_lstclear(t_tokens **lst, void (*del)(void *))
{
	t_tokens	*t;
	t_tokens	*buf;

	if (!*lst)
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

void	ft_lstdelone(t_tokens *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	(*del)(lst->string);
	lst->string = NULL;
	free(lst);
	lst = NULL;
}

void	free_tree(t_ast **ast)
{
	if (!*ast)
		return ;
	free_tree(&(*ast)->left);
	free_tree(&(*ast)->right);
	ft_lstclear(&(*ast)->tokens, &free);
	free(*ast);
	*ast = NULL;
}

void	freetabs(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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
		free(t);
		t = buf;
	}
	*lst = NULL;
}
void	super_free(char **__ptr)
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
		ft_lstclear(&vars->tokens, &free);
	}
	free_files(&vars->cmd.infiles);
	free_files(&vars->cmd.outfiles);
	super_free(&vars->str_in.buff);
	super_free(&vars->prompt);
	if (i == FREE_BUILTIN || i == FREE_FULL)
	{
		freetabs(vars->cmd.argv);
		super_free(&vars->cmd.path);
		if (i == FREE_FULL)
		{
			freetabs(vars->envl);
			freetabs(vars->cmd.env_paths);
			rl_clear_history();
		}
	}
}
