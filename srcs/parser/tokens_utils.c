/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:16:58 by bmoudach          #+#    #+#             */
/*   Updated: 2023/11/26 18:35:42 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_lstsize(t_tokens *lst)
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

t_tokens	*ft_lstlast(t_tokens **tok)
{
	t_tokens	*tmp;

	tmp = *tok;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_tokens	*ft_lstnew(char *content, int type, int *expand)
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

void	ft_lstadd_back(t_tokens **tok, t_tokens *new)
{
	t_tokens	*tmp;

	if (tok)
	{
		if (*tok == NULL)
			*tok = new;
		else
		{
			tmp = ft_lstlast(tok);
			tmp->next = new;
		}
	}
}

void	ft_lstadd_front(t_tokens **tok, t_tokens *new)
{
	if (tok)
	{
		if (*tok)
			new->next = *tok;
		*tok = new;
	}
}
