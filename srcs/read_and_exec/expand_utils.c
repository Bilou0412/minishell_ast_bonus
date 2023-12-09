/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 18:22:13 by soutin            #+#    #+#             */
/*   Updated: 2023/12/09 18:22:14 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_char_in_str(char *str, char c)
{
	int	i;
	int	number_of_char;

	i = 0;
	number_of_char = 0;
	while (str[i])
	{
		if (str[i] == c)
			number_of_char++;
		i++;
	}
	return (number_of_char);
}

t_expand	*ft_explast(t_expand **lst_expand)
{
	t_expand	*tmp;

	tmp = *lst_expand;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_exp_add_back(t_expand **expand, t_expand *new)
{
	t_expand	*tmp;

	if (expand)
	{
		if (*expand == NULL)
			*expand = new;
		else
		{
			tmp = ft_explast(expand);
			tmp->next = new;
		}
	}
}

t_expand	*ft_expand_new(char *content)
{
	t_expand	*new;

	new = (t_expand *)ft_calloc(1, sizeof(*new));
	if (!new)
		return (NULL);
	new->to_expand = content;
	new->next = NULL;
	return (new);
}

void	content_to_lst_expand(char *to_expand, t_expand **expand)
{
	t_expand	*node;

	node = (t_expand *)ft_collector(ft_expand_new(to_expand), false);
	ft_exp_add_back(expand, node);
}
