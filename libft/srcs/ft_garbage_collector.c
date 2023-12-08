/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:26:29 by soutin            #+#    #+#             */
/*   Updated: 2023/12/08 17:14:09 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	del_a_garbage(t_list **lst, void *ptr)
{
	t_list	*t;
	t_list	*buf;

	t = *lst;
	if (!lst)
		return ;
	while (t->next)
	{
		if (t->next->content == ptr)
		{
			buf = t->next->next;
			free(ptr);
			ptr = NULL;
			free(t->next);
			t->next = buf;
			return ;
		}
		t = t->next;
	}
}

void	*ft_collector(void *ptr, bool clean)
{
	static t_list	*lst;
	
	if (clean)
	{
		if (!ptr)
			ft_lstclear(&lst, &free);
		else
			del_a_garbage(&lst, ptr);
	}
	else
	{
		if (ft_lstadd_back(&lst, ft_lstnew(ptr)) < 0)
		{
			ft_putstr_fd("memory allocation error\n", 2);
			ft_collector(NULL, true);
			exit(1);
		}
		return (ptr);
	}
	return (NULL);
}