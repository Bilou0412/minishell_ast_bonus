/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:15:26 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/21 19:48:57 by soutin           ###   ########.fr       */
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
	if (!*tab)
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

void	freevars(t_vars *vars, int i)
{
	free_tree(&vars->ast);
	ft_lstclear(&vars->tokens, &free);
	free_files(&vars->cmd.infiles);
	free_files(&vars->cmd.outfiles);
	if (vars->str_in.buff)
	{
		free(vars->str_in.buff);
		vars->str_in.buff = NULL;
	}
	if (vars->prompt)
	{
		free(vars->prompt);
		vars->prompt = NULL;
	}
	if (i == free_builtin || i == free_full)
	{
		if (i == free_full)
		{
			freetabs(vars->envl);
			freetabs(vars->cmd.env_paths);
		}
		freetabs(vars->cmd.argv);
		if (vars->cmd.path)
			free(vars->cmd.path);
		
	}
}
