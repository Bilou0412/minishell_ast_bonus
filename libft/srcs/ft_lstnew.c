/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:53:58 by soutin            #+#    #+#             */
/*   Updated: 2023/12/05 19:53:14 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstnew(void *content, int fd)
{
	t_list	*c;

	if (!content)
		return (NULL);
	c = ft_calloc(1, sizeof(*c));
	if (!c)
		return (NULL);
	c->content = content;
	c->fd = fd;
	c->next = NULL;
	return (c);
}
