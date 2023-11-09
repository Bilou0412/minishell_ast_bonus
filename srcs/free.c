/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:15:26 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/09 18:00:13 by soutin           ###   ########.fr       */
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
	free(lst);
}

void	free_tree(t_ast **ast)
{
	if (!*ast)
		return ;
	free_tree(&(*ast)->left);
	free_tree(&(*ast)->right);
	ft_lstclear(&(*ast)->tokens, &free);
	free(*ast);
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
}

void	freevars(t_vars *vars, int i)
{
	free_tree(&vars->ast);
	ft_lstclear(&vars->tokens, &free);
	if (vars->cmd.argv_cmd)
		free(vars->cmd.argv_cmd);
	if (vars->str_in.buff)
		free(vars->str_in.buff);
	if (vars->prompt)
		free(vars->prompt);
}
