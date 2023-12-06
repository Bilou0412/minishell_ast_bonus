/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:53:58 by soutin            #+#    #+#             */
/*   Updated: 2023/12/06 14:49:26 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*c;

	if (!content)
		return (NULL);
	c = ft_calloc(1, sizeof(*c));
	if (!c)
		return (NULL);
	c->content = content;
	c->next = NULL;
	return (c);
}
