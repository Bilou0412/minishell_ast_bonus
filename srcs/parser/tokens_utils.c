/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:16:58 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/30 21:00:21 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_toksize(t_tokens *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_tokens	*ft_toklast(t_tokens **tok)
{
	t_tokens	*tmp;

	tmp = *tok;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_tokens	*ft_toknew(char *content, int type, int *expand)
{
	t_tokens	*new;

	new = (t_tokens *)ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->string = content;
	new->type = type;
	new->expand = expand;
	new->next = NULL;
	return (new);
}

void	ft_tokadd_back(t_tokens **tok, t_tokens *new)
{
	t_tokens	*tmp;

	if (tok)
	{
		if (*tok == NULL)
			*tok = new;
		else
		{
			tmp = ft_toklast(tok);
			tmp->next = new;
		}
	}
}

void	ft_tokadd_front(t_tokens **tok, t_tokens *new)
{
	if (tok)
	{
		if (*tok)
			new->next = *tok;
		*tok = new;
	}
}
